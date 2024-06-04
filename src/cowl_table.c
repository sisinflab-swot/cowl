/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_table.h"
#include "cowl_any.h"
#include "cowl_iterator.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"
#include "cowl_primitive_private.h" // IWYU pragma: keep, needed for cowl_primitive_equals
#include "cowl_string_private.h"    // IWYU pragma: keep, needed for cowl_string_equals
#include "cowl_table_private.h"
#include "ulib.h"
#include <stddef.h>

UHASH_IMPL_PI(CowlObjectTable, cowl_hash, cowl_equals)

#define HASH_GEN(T, TYPE)                                                                          \
    static ulib_uint T##_hash(CowlAny *obj) {                                                      \
        return cowl_##T##_hash(obj);                                                               \
    }                                                                                              \
    static bool T##_equals(CowlAny *lhs, CowlAny *rhs) {                                           \
        return cowl_##T##_equals(lhs, rhs);                                                        \
    }                                                                                              \
    UHash(CowlObjectTable) cowl_##T##_##TYPE(void) {                                               \
        return uh##TYPE##_pi(CowlObjectTable, T##_hash, T##_equals);                               \
    }

HASH_GEN(primitive, map)
HASH_GEN(string, map)

CowlTable *cowl_table(UHash(CowlObjectTable) *table) {
    CowlTable *tbl = ulib_alloc(tbl);

    if (!tbl) {
        uhash_deinit(CowlObjectTable, table);
        return NULL;
    }

    *tbl = (CowlTable){ .super = COWL_OBJECT_INIT(COWL_OT_TABLE),
                        .data = table ? uhash_move(CowlObjectTable, table)
                                      : uhset(CowlObjectTable) };

    cowl_table_foreach (tbl, obj) {
        cowl_retain(*obj.key);
        if (obj.val && *obj.val) cowl_retain(*obj.val);
    }

    return tbl;
}

void cowl_table_free_ex(CowlTable *table, bool release_elements) {
    if (release_elements) {
        cowl_table_foreach (table, obj) {
            cowl_release(*obj.key);
            if (obj.val) cowl_release(*obj.val);
        }
    }

    uhash_deinit(CowlObjectTable, &table->data);
    ulib_free(table);
}

void cowl_table_free(CowlTable *table) {
    cowl_table_free_ex(table, true);
}

void cowl_table_release_ex(CowlTable *table, bool release_elements) {
    if (table && !cowl_object_decr_ref(table)) {
        cowl_table_free_ex(table, release_elements);
    }
}

UHash(CowlObjectTable) const *cowl_table_get_data(CowlTable *table) {
    static UHash(CowlObjectTable) const empty_data = { 0 };
    return table ? &table->data : &empty_data;
}

bool cowl_table_equals(CowlTable *lhs, CowlTable *rhs) {
    if (!uhset_equals(CowlObjectTable, &lhs->data, &rhs->data)) return false;

    bool lhs_is_map = uhash_is_map(CowlObjectTable, &lhs->data);
    bool rhs_is_map = uhash_is_map(CowlObjectTable, &rhs->data);
    if (!lhs_is_map) return !rhs_is_map;
    if (!rhs_is_map) return false;

    cowl_table_foreach (lhs, e) {
        CowlAny *r_val = cowl_table_get_value(rhs, *e.key);
        if (r_val == *e.val) return true;
        if (!(r_val && cowl_equals(*e.val, r_val))) return false;
    }

    return true;
}

ulib_uint cowl_table_hash(CowlTable *table) {
    return uhset_hash(CowlObjectTable, &table->data);
}

bool cowl_table_iterate_primitives(CowlTable *table, CowlPrimitiveFlags flags, CowlIterator *iter) {
    cowl_table_foreach (table, obj) {
        if (!cowl_iterate_primitives(*obj.key, flags, iter)) return false;
        if (obj.val && *obj.val && !cowl_iterate_primitives(*obj.val, flags, iter)) return false;
    }
    return true;
}
