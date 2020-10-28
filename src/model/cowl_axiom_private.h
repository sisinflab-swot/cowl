/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_PRIVATE_H
#define COWL_AXIOM_PRIVATE_H

#include "cowl_axiom.h"
#include "cowl_annotation_vec.h"
#include "cowl_hash_utils.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAxiom) {
    CowlHashObject super;
};

#define cowl_axiom_struct(T, FIELDS)                                                                \
    cowl_struct(T) {                                                                                \
        CowlAxiom super;                                                                            \
        FIELDS                                                                                      \
        CowlAnnotationVec *annot[];                                                                 \
    }

#define cowl_axiom_alloc(AXIOM, ANNOT) \
    cowl_malloc(sizeof(*(AXIOM)) + ((ANNOT) ? sizeof(CowlAnnotationVec*) : 0))

#define cowl_axiom_init(T, AXIOM, ANNOT, ...) do {                                                  \
    *(AXIOM) = (T){__VA_ARGS__};                                                                    \
    if (ANNOT) (AXIOM)->annot[0] = (ANNOT);                                                         \
} while (0)

#define COWL_AXIOM_INIT(T, H, A) {                                                                  \
    .super = COWL_HASH_OBJECT_BIT_INIT((CowlObjectType)(T) + COWL_OT_A_DECL, A, H),                \
}

#define cowl_axiom_free(AXIOM) do {                                                                 \
    if (cowl_axiom_has_annot(AXIOM)) cowl_annotation_vec_free((AXIOM)->annot[0]);                   \
    cowl_free(AXIOM);                                                                               \
} while(0)

#define cowl_axiom_has_annot(AXIOM) cowl_object_flags_has_bit(((CowlObject *)(AXIOM))->flags)
#define cowl_axiom_get_annot(AXIOM) (cowl_axiom_has_annot(AXIOM) ? (AXIOM)->annot[0] : NULL)

#define cowl_axiom_equals_impl(LHS, RHS, EXP) (                                                     \
    cowl_hash_object_equals_impl(LHS, RHS) && (EXP) &&                                              \
    (!cowl_axiom_has_annot(LHS) || cowl_annotation_vec_equals((LHS)->annot[0], (RHS)->annot[0]))    \
)

#define cowl_axiom_hash_1(INIT, ANNOT, A)                                                           \
    ((ANNOT) ? cowl_hash_2(INIT, A, cowl_annotation_vec_hash(ANNOT)) :                              \
     cowl_hash_1(INIT, A))

#define cowl_axiom_hash_2(INIT, ANNOT, A, B)                                                        \
    ((ANNOT) ? cowl_hash_3(INIT, A, B, cowl_annotation_vec_hash(ANNOT)) :                           \
     cowl_hash_2(INIT, A, B))

#define cowl_axiom_hash_3(INIT, ANNOT, A, B, C)                                                     \
    ((ANNOT) ? cowl_hash_4(INIT, A, B, C, cowl_annotation_vec_hash(ANNOT)) :                        \
     cowl_hash_3(INIT, A, B, C))

#define cowl_axiom_hash_4(INIT, ANNOT, A, B, C, D)                                                  \
    ((ANNOT) ? cowl_hash_5(INIT, A, B, C, D, cowl_annotation_vec_hash(ANNOT)) :                     \
     cowl_hash_4(INIT, A, B, C, D))

#define cowl_axiom_annot_iterate(AXIOM, ITER)                                                       \
    (!cowl_axiom_has_annot(AXIOM) ||                                                                \
     cowl_annotation_vec_iterate((AXIOM)->annot[0], ITER))

COWL_END_DECLS

#endif // COWL_AXIOM_PRIVATE_H
