/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_table_private.h"
#include "cowl_annot_prop.h"
#include "cowl_anon_ind.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"
#include "cowl_object.h"
#include "cowl_string.h"

static ulib_uint cowl_object_table_hash(void *k) { return cowl_object_hash(k); }
static bool cowl_object_table_equals(void *a, void *b) { return cowl_object_equals(a, b); }
UHASH_IMPL_PI(CowlObjectTable, cowl_object_table_hash, cowl_object_table_equals)

#define HASH_GEN(T, TYPE)                                                                           \
    static ulib_uint T##_hash(void *obj) { return cowl_##T##_hash(obj); }                           \
    static bool T##_equals(void *lhs, void *rhs) { return cowl_##T##_equals(lhs, rhs); }            \
    UHash(CowlObjectTable)* cowl_##T##_##TYPE##_alloc(void) {                                       \
        return uh##TYPE##_alloc_pi(CowlObjectTable, T##_hash, T##_equals);                          \
    }

HASH_GEN(annot_prop, map)
HASH_GEN(anon_ind, map)
HASH_GEN(class, map)
HASH_GEN(data_prop, map)
HASH_GEN(datatype, map)
HASH_GEN(named_ind, map)
HASH_GEN(obj_prop, map)
HASH_GEN(string, map)

void cowl_object_set_free(CowlObjectTable *set) {
    if (!set) return;
    uhash_foreach_key(CowlObjectTable, set, obj, cowl_object_release(obj));
    uhash_free(CowlObjectTable, (UHash(CowlObjectTable)*)set);
}

bool cowl_object_set_equals(CowlObjectTable *lhs, CowlObjectTable *rhs) {
    return uhset_equals(CowlObjectTable, lhs, rhs);
}

ulib_uint cowl_object_set_hash(CowlObjectTable *set) {
    return uhset_hash(CowlObjectTable, set);
}

cowl_ret cowl_object_set_insert(UHash(CowlObjectTable) *set, CowlObject *object) {
    uhash_ret ret = uhset_insert(CowlObjectTable, set, object);
    if (ret == UHASH_INSERTED) cowl_object_retain(object);
    return ret == UHASH_ERR ? COWL_ERR_MEM : COWL_OK;
}

bool cowl_object_set_iterate_primitives(CowlObjectTable *set, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    uhash_foreach_key(CowlObjectTable, set, obj, {
        if (!cowl_object_iterate_primitives(obj, flags, iter)) return false;
    });
    return true;
}
