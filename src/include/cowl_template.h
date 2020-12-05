/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEMPLATE_H
#define COWL_TEMPLATE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

#define COWL_INST_TBL_GET_IMPL(UC, LC, KEY_INIT, VALUE_ALLOC) {                                     \
    uhash_uint idx;                                                                                 \
    Cowl##UC key = KEY_INIT;                                                                        \
    uhash_ret ret = uhash_put(Cowl##UC##Table, inst_tbl, &key, &idx);                               \
                                                                                                    \
    Cowl##UC *var = NULL;                                                                           \
                                                                                                    \
    if (ret == UHASH_INSERTED) {                                                                    \
        var = VALUE_ALLOC;                                                                          \
        if (var) {                                                                                  \
            uhash_key(inst_tbl, idx) = var;                                                         \
        } else {                                                                                    \
            uhash_delete(Cowl##UC##Table, inst_tbl, idx);                                           \
        }                                                                                           \
    } else if (ret == UHASH_PRESENT) {                                                              \
        var = uhash_key(inst_tbl, idx);                                                             \
        (void)cowl_object_retain(var);                                                              \
    }                                                                                               \
                                                                                                    \
    return var;                                                                                     \
}

#define COWL_ENTITY_FROM_CSTRING_IMPL(UC, LC) {                                                     \
    Cowl##UC *var = NULL;                                                                           \
    CowlIRI *iri = cowl_iri_from_cstring(cstring, length);                                          \
                                                                                                    \
    if (iri) {                                                                                      \
        var = cowl_##LC##_get(iri);                                                                 \
        cowl_iri_release(iri);                                                                      \
    }                                                                                               \
                                                                                                    \
    return var;                                                                                     \
}

#define COWL_TO_STRING_IMPL(LC, VAR) {                                                              \
    CowlStrBuf buf = cowl_str_buf_init;                                                             \
                                                                                                    \
    if (cowl_str_buf_append_##LC(&buf, (VAR))) {                                                    \
        cowl_str_buf_deinit(&buf);                                                                  \
        return NULL;                                                                                \
    }                                                                                               \
                                                                                                    \
    return cowl_str_buf_to_string(&buf);                                                            \
}

COWL_END_DECLS

#endif // COWL_TEMPLATE_H
