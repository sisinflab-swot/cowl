/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error_handler.h"
#include "cowl_iri.h"
#include "cowl_istream.h"
#include "cowl_manager_private.h"
#include "cowl_ontology.h"
#include "cowl_ostream.h"
#include "cowl_string_private.h"

static CowlErrorHandler cowl_best_error_handler(CowlAny *origin) {
    CowlManager *manager = NULL;

    switch (cowl_get_type(origin)) {
        case COWL_OT_ONTOLOGY: manager = cowl_ontology_get_manager(origin); break;
        case COWL_OT_ISTREAM: manager = cowl_istream_get_manager(origin); break;
        case COWL_OT_OSTREAM: manager = cowl_ostream_get_manager(origin); break;
        case COWL_OT_MANAGER: manager = origin; break;
        default: break;
    }

    return cowl_manager_get_error_handler(manager);
}

cowl_ret cowl_handle_error(cowl_ret code, UString desc, CowlAny *origin) {
    if (code == COWL_ERR_SYNTAX) {
        cowl_handle_syntax_error(desc, origin, (CowlErrorLoc){ 0 });
        return code;
    }

    CowlErrorHandler handler = cowl_best_error_handler(origin);
    if (!handler.handle_error) return code;

    if (ustring_is_empty(desc)) desc = cowl_ret_to_ustring(code);
    CowlString description = cowl_string_init(desc);

    CowlError error = {
        .code = code,
        .origin = origin,
        .description = cowl_string_get_length(&description) ? &description : NULL,
    };

    handler.handle_error(handler.ctx, &error);
    return code;
}

cowl_ret cowl_handle_syntax_error(UString desc, CowlAny *origin, CowlErrorLoc loc) {
    CowlErrorHandler handler = cowl_best_error_handler(origin);
    if (!handler.handle_error) return COWL_ERR_SYNTAX;

    bool release_source = false;

    if (!loc.source && cowl_get_type(origin) == COWL_OT_ONTOLOGY) {
        loc.source = cowl_to_string(cowl_ontology_get_id(origin).iri);
        release_source = true;
    }

    CowlString description = cowl_string_init(desc);

    CowlSyntaxError error = {
        .super = {
            .code = COWL_ERR_SYNTAX,
            .origin = origin,
            .description = cowl_string_get_length(&description) ? &description : NULL,
        },
        .loc = loc,
    };

    handler.handle_error(handler.ctx, (CowlError *)&error);
    if (release_source) cowl_release(loc.source);
    return COWL_ERR_SYNTAX;
}

cowl_ret cowl_handle_error_code(cowl_ret code, CowlAny *origin) {
    return cowl_handle_error(code, ustring_empty, origin);
}

cowl_ret cowl_handle_stream_error(ustream_ret code, CowlAny *origin) {
    return cowl_handle_error_code(cowl_ret_from_ustream(code), origin);
}

cowl_ret cowl_handle_path_error(UString path, UString reason, CowlAny *origin) {
    UString comp[] = { reason, ustring_literal(" "), path };
    UString desc = ustring_concat(comp, ulib_array_count(comp));
    cowl_handle_error(COWL_ERR_IO, desc, origin);
    ustring_deinit(&desc);
    return COWL_ERR_IO;
}
