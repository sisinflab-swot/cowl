/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_PRIVATE_H
#define COWL_AXIOM_PRIVATE_H

#include "cowl_axiom.h"
#include "cowl_annotation.h"
#include "cowl_hash_utils.h"
#include "cowl_object_private.h"
#include "cowl_object_vec_private.h"

COWL_BEGIN_DECLS

struct CowlAxiom {
    CowlHashObject super;
};

#define cowl_axiom_struct(T, FIELDS)                                                                \
    struct T {                                                                                \
        CowlAxiom super;                                                                            \
        FIELDS                                                                                      \
        CowlObjectVec *annot[];                                                                     \
    }

#define cowl_axiom_alloc(AXIOM, ANNOT) \
    ulib_malloc(sizeof(*(AXIOM)) + ((ANNOT) ? sizeof(CowlObjectVec*) : 0))

#define cowl_axiom_init(T, AXIOM, ANNOT, ...) do {                                                  \
    *(AXIOM) = (T){__VA_ARGS__};                                                                    \
    if (ANNOT) (AXIOM)->annot[0] = (ANNOT);                                                         \
} while (0)

#define COWL_AXIOM_INIT(T, H, A) {                                                                  \
    .super = COWL_HASH_OBJECT_BIT_INIT((CowlObjectType)(T) + COWL_OT_A_DECL, A, H),                 \
}

#define cowl_axiom_free(AXIOM) do {                                                                 \
    if (cowl_axiom_has_annot(AXIOM)) cowl_object_vec_free_spec(annotation, (AXIOM)->annot[0]);      \
    ulib_free(AXIOM);                                                                               \
} while(0)

#define cowl_axiom_has_annot(AXIOM) cowl_object_bit_get(AXIOM)
#define cowl_axiom_get_annot(AXIOM) (cowl_axiom_has_annot(AXIOM) ? (AXIOM)->annot[0] : NULL)

#define cowl_axiom_equals_impl(LHS, RHS, EXP) (                                                     \
    cowl_object_hash_equals(LHS, RHS) &&                                                            \
    (EXP) &&                                                                                        \
    (!cowl_axiom_has_annot(LHS) || cowl_object_vec_equals((LHS)->annot[0], (RHS)->annot[0]))        \
)

#define cowl_axiom_hash_1(INIT, ANNOT, A)                                                           \
    ((ANNOT) ? cowl_hash_2(INIT, A, cowl_object_vec_hash(ANNOT)) :                                  \
     cowl_hash_1(INIT, A))

#define cowl_axiom_hash_2(INIT, ANNOT, A, B)                                                        \
    ((ANNOT) ? cowl_hash_3(INIT, A, B, cowl_object_vec_hash(ANNOT)) :                               \
     cowl_hash_2(INIT, A, B))

#define cowl_axiom_hash_3(INIT, ANNOT, A, B, C)                                                     \
    ((ANNOT) ? cowl_hash_4(INIT, A, B, C, cowl_object_vec_hash(ANNOT)) :                            \
     cowl_hash_3(INIT, A, B, C))

#define cowl_axiom_hash_4(INIT, ANNOT, A, B, C, D)                                                  \
    ((ANNOT) ? cowl_hash_5(INIT, A, B, C, D, cowl_object_vec_hash(ANNOT)) :                         \
     cowl_hash_4(INIT, A, B, C, D))

#define cowl_axiom_annot_iterate_primitives(AXIOM, FLAGS, ITER)                                     \
    (!cowl_axiom_has_annot(AXIOM) ||                                                                \
     cowl_object_vec_iterate_primitives((AXIOM)->annot[0], FLAGS, ITER))

COWL_END_DECLS

#endif // COWL_AXIOM_PRIVATE_H
