/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEMPLATE_H
#define COWL_TEMPLATE_H

#include "cowl_std.h"
#include "cowl_stream.h"
#include "cowl_string_private.h"

COWL_BEGIN_DECLS

#define COWL_INST_TBL_GET_IMPL(UC, LC, KEY_INIT, VALUE_ALLOC) {                                     \
    ulib_uint idx;                                                                                  \
    Cowl##UC key = KEY_INIT;                                                                        \
    uhash_ret ret = uhash_put(CowlObjectTable, inst_tbl, &key, &idx);                               \
                                                                                                    \
    Cowl##UC *var = NULL;                                                                           \
                                                                                                    \
    if (ret == UHASH_INSERTED) {                                                                    \
        var = VALUE_ALLOC;                                                                          \
        if (var) {                                                                                  \
            uhash_key(inst_tbl, idx) = var;                                                         \
        } else {                                                                                    \
            uhash_delete(CowlObjectTable, inst_tbl, idx);                                           \
        }                                                                                           \
    } else if (ret == UHASH_PRESENT) {                                                              \
        var = uhash_key(inst_tbl, idx);                                                             \
        (void)cowl_object_incr_ref(var);                                                            \
    }                                                                                               \
                                                                                                    \
    return var;                                                                                     \
}

#define COWL_ENTITY_FROM_STRING_IMPL(UC, LC) {                                                      \
    Cowl##UC *var = NULL;                                                                           \
    CowlIRI *iri = cowl_iri_from_string(string);                                                    \
                                                                                                    \
    if (iri) {                                                                                      \
        var = cowl_##LC##_get(iri);                                                                 \
        cowl_iri_release(iri);                                                                      \
    }                                                                                               \
                                                                                                    \
    return var;                                                                                     \
}

#define COWL_TO_STRING_IMPL(LC, VAR) {                                                              \
    CowlString *string = NULL;                                                                      \
    UOStream stream;                                                                                \
    UStrBuf buf = ustrbuf_init();                                                                   \
    if (uostream_to_strbuf(&stream, &buf) == USTREAM_OK) {                                          \
        if (cowl_stream_write_##LC(&stream, (VAR)) == USTREAM_OK) {                                 \
            string = cowl_string_alloc(ustrbuf_to_ustring(&buf));                                   \
        }                                                                                           \
        uostream_deinit(&stream);                                                                   \
    }                                                                                               \
    ustrbuf_deinit(buf);                                                                            \
    return string;                                                                                  \
}

COWL_END_DECLS

#endif // COWL_TEMPLATE_H
