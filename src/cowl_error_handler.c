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
#include "cowl_config_private.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology.h"
#include "cowl_stream.h"
#include "cowl_string_private.h"

static CowlErrorHandler cowl_best_error_handler(CowlObject *origin) {
    CowlManager *manager = NULL;

    switch (cowl_get_type(origin)) {
        case COWL_OT_ONTOLOGY: manager = cowl_ontology_get_manager((CowlOntology *)origin); break;
        case COWL_OT_STREAM: manager = cowl_stream_get_manager((CowlStream *)origin); break;
        case COWL_OT_MANAGER: manager = (CowlManager *)origin; break;
        default: break;
    }

    CowlErrorHandler handler = manager ? manager->handler : (CowlErrorHandler){ 0 };
    if (!handler.handle_error) handler = cowl_get_error_handler();

    return handler;
}

void cowl_handle_error(cowl_ret code, UString desc, CowlAny *origin) {
    if (code == COWL_ERR_SYNTAX) {
        cowl_handle_syntax_error(desc, origin, (CowlErrorLoc){ 0 });
        return;
    }

    CowlErrorHandler handler = cowl_best_error_handler(origin);
    if (!handler.handle_error) return;

    if (ustring_is_empty(desc)) desc = cowl_ret_to_ustring(code);
    CowlString description = cowl_string_init(desc);

    CowlError error = {
        .code = code,
        .origin = origin,
        .description = cowl_string_get_length(&description) ? &description : NULL,
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_handle_syntax_error(UString desc, CowlAny *origin, CowlErrorLoc loc) {
    CowlErrorHandler handler = cowl_best_error_handler(origin);
    if (!handler.handle_error) return;

    bool release_source = false;

    if (!loc.source && cowl_get_type(origin) == COWL_OT_ONTOLOGY) {
        loc.source = cowl_iri_to_string(cowl_ontology_get_id(origin).iri);
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
    if (release_source) cowl_string_release(loc.source);
}

void cowl_handle_error_code(cowl_ret code, CowlAny *origin) {
    cowl_handle_error(code, ustring_empty, origin);
}

void cowl_handle_stream_error(ustream_ret code, CowlAny *origin) {
    cowl_handle_error_code(cowl_ret_from_ustream(code), origin);
}
