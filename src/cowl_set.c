/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_set_private.h"
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
    UHash(CowlObjectTable) cowl_##T##_##TYPE##_init(void) {                                         \
        return uh##TYPE##_init_pi(CowlObjectTable, T##_hash, T##_equals);                           \
    }

HASH_GEN(annot_prop, map)
HASH_GEN(anon_ind, map)
HASH_GEN(class, map)
HASH_GEN(data_prop, map)
HASH_GEN(datatype, map)
HASH_GEN(named_ind, map)
HASH_GEN(obj_prop, map)
HASH_GEN(string, map)

static CowlSet* cowl_set_alloc(UHash(CowlObjectTable) *data) {
    CowlSet *set = ulib_alloc(set);
    if (!set) return NULL;

    *set = (CowlSet) {
        .super = COWL_OBJECT_INIT(COWL_OT_SET),
        .data = data ? uhash_move(CowlObjectTable, data) : uhset_init(CowlObjectTable)
    };

    uhash_foreach(CowlObjectTable, &set->data, obj) {
        cowl_object_retain(*obj.key);
    }

    return set;
}

static void cowl_set_free(CowlSet *set) {
    uhash_foreach(CowlObjectTable, &set->data, obj) { cowl_object_release(*obj.key); }
    uhash_deinit(CowlObjectTable, &set->data);
    ulib_free(set);
}

CowlSet* cowl_set_get(UHash(CowlObjectTable) *set) {
    return cowl_set_alloc(set);
}

CowlSet* cowl_set_retain(CowlSet *vec) {
    return cowl_object_incr_ref(vec);
}

void cowl_set_release(CowlSet *vec) {
    if (vec && !cowl_object_decr_ref(vec)) {
        cowl_set_free(vec);
    }
}

UHash(CowlObjectTable) const* cowl_set_get_data(CowlSet *set) {
    return &set->data;
}

bool cowl_set_equals(CowlSet *lhs, CowlSet *rhs) {
    return uhset_equals(CowlObjectTable, &lhs->data, &rhs->data);
}

ulib_uint cowl_set_hash(CowlSet *set) {
    return uhset_hash(CowlObjectTable, &set->data);
}

bool cowl_set_iterate_primitives(CowlSet *set, CowlPrimitiveFlags flags, CowlIterator *iter) {
    uhash_foreach(CowlObjectTable, &set->data, obj) {
        if (!cowl_object_iterate_primitives(*obj.key, flags, iter)) return false;
    }
    return true;
}
