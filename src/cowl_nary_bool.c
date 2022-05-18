/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_nary_bool_private.h"
#include "cowl_hash_utils.h"
#include "cowl_macros.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlNAryBool* cowl_nary_bool_alloc(CowlObjectType type, CowlVector *operands) {
    CowlNAryBool *exp = ulib_alloc(exp);
    if (!exp) return NULL;

    *exp = (CowlNAryBool) {
        .super = COWL_OBJECT_INIT(type),
        .operands = cowl_vector_retain(operands)
    };

    return exp;
}

static void cowl_nary_bool_free(CowlNAryBool *exp) {
    cowl_vector_release(exp->operands);
    ulib_free(exp);
}

CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlVector *operands) {
    if (!(operands && cowl_enum_value_is_valid(NT, type))) return NULL;
    return cowl_nary_bool_alloc(COWL_OT_CE_OBJ_INTERSECT + type, operands);
}

CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp) {
    return cowl_object_incr_ref(exp);
}

void cowl_nary_bool_release(CowlNAryBool *exp) {
    if (exp && !cowl_object_decr_ref(exp)) {
        cowl_nary_bool_free(exp);
    }
}

CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp) {
    return (CowlNAryType)(cowl_get_type(exp) - COWL_OT_CE_OBJ_INTERSECT);
}

CowlVector* cowl_nary_bool_get_operands(CowlNAryBool *exp) {
    return exp->operands;
}

CowlString* cowl_nary_bool_to_string(CowlNAryBool *exp)
    COWL_TO_STRING_IMPL(nary_bool, exp)

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs) {
    return cowl_object_type_equals(lhs, rhs) &&
           cowl_vector_equals(lhs->operands, rhs->operands);
}

ulib_uint cowl_nary_bool_hash(CowlNAryBool *exp) {
    return cowl_hash_2(COWL_HASH_INIT_NARY_BOOL,
                       cowl_nary_bool_get_type(exp),
                       cowl_vector_hash(exp->operands));
}

bool cowl_nary_bool_iterate_primitives(CowlNAryBool *exp, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_vector_iterate_primitives(exp->operands, flags, iter);
}
