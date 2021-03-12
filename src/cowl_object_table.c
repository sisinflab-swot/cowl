/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_table_private.h"
#include "cowl_annot_prop.h"
#include "cowl_anon_ind.h"
#include "cowl_axiom.h"
#include "cowl_class.h"
#include "cowl_cls_exp.h"
#include "cowl_data_prop.h"
#include "cowl_data_prop_exp.h"
#include "cowl_data_range.h"
#include "cowl_datatype.h"
#include "cowl_facet_restr.h"
#include "cowl_individual.h"
#include "cowl_literal.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_object.h"
#include "cowl_string.h"

UHASH_IMPL_PI(CowlObjectTable)

#define HASH_GEN(T, TYPE)                                                                           \
    static cowl_uint T##_hash(void *obj) { return cowl_##T##_hash(obj); }                           \
    static bool T##_equals(void *lhs, void *rhs) { return cowl_##T##_equals(lhs, rhs); }            \
    UHash(CowlObjectTable)* cowl_##T##_##TYPE##_alloc(void) {                                       \
        return uh##TYPE##_alloc_pi(CowlObjectTable, T##_hash, T##_equals);                          \
    }

HASH_GEN(annot_prop, map)
HASH_GEN(anon_ind, map)
HASH_GEN(axiom, set)
HASH_GEN(class, map)
HASH_GEN(cls_exp, set)
HASH_GEN(data_prop, map)
HASH_GEN(data_prop_exp, set)
HASH_GEN(data_range, set)
HASH_GEN(datatype, map)
HASH_GEN(facet_restr, set)
HASH_GEN(individual, set)
HASH_GEN(literal, set)
HASH_GEN(named_ind, map)
HASH_GEN(obj_prop, map)
HASH_GEN(obj_prop_exp, set)
HASH_GEN(string, map)

void cowl_object_set_free(CowlObjectTable *set) {
    if (!set) return;
    uhash_foreach_key(CowlObjectTable, set, obj, cowl_object_release(obj));
    uhash_free(CowlObjectTable, (UHash(CowlObjectTable)*)set);
}

bool cowl_object_set_equals(CowlObjectTable *lhs, CowlObjectTable *rhs) {
    return uhset_equals(CowlObjectTable, lhs, rhs);
}

cowl_uint cowl_object_set_hash(CowlObjectTable *set) {
    return uhset_hash(CowlObjectTable, set);
}

cowl_ret cowl_object_set_insert(UHash(CowlObjectTable) *set, CowlObject *object) {
    uhash_ret ret = uhset_insert(CowlObjectTable, set, object);
    if (ret == UHASH_INSERTED) cowl_object_retain(object);
    return ret == UHASH_ERR ? COWL_ERR_MEM : COWL_OK;
}

bool cowl_object_set_iterate_primitives(CowlObjectTable *set, CowlIterator *iter,
                                        CowlPrimitiveFlags flags) {
    uhash_foreach_key(CowlObjectTable, set, obj, {
        if (!cowl_object_iterate_primitives(obj, iter, flags)) return false;
    });
    return true;
}