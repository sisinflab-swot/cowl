/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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
#include "cowl_vector.h"

COWL_BEGIN_DECLS

struct CowlAxiom {
    CowlObject super;
};

#define cowl_axiom_struct(T, FIELDS)                                                                \
    struct T {                                                                                      \
        CowlAxiom super;                                                                            \
        FIELDS                                                                                      \
        CowlVector *annot[];                                                                        \
    }

#define cowl_axiom_alloc(AXIOM, ANNOT) \
    ulib_malloc(sizeof(*(AXIOM)) + ((ANNOT) ? sizeof(CowlVector*) : 0))

#define cowl_axiom_init(T, AXIOM, ANNOT, ...) do {                                                  \
    *(AXIOM) = (T){__VA_ARGS__};                                                                    \
    if (ANNOT) (AXIOM)->annot[0] = cowl_vector_retain(ANNOT);                                       \
} while(0)

#define COWL_AXIOM_INIT(T, A) {                                                                     \
    .super = COWL_OBJECT_BIT_INIT((CowlObjectType)(T) + COWL_OT_A_DECL, A)                          \
}

#define cowl_axiom_free(AXIOM) do {                                                                 \
    if (cowl_axiom_has_annot(AXIOM)) cowl_vector_release((AXIOM)->annot[0]);                        \
    ulib_free(AXIOM);                                                                               \
} while(0)

#define cowl_axiom_has_annot(AXIOM) cowl_object_bit_get(AXIOM)
#define cowl_axiom_get_annot(AXIOM) (cowl_axiom_has_annot(AXIOM) ? (AXIOM)->annot[0] : NULL)

#define cowl_axiom_equals_impl(LHS, RHS, EXP) (                                                     \
    (EXP) &&                                                                                        \
    (!(cowl_axiom_has_annot(LHS) && cowl_axiom_has_annot(RHS)) ||                                   \
     cowl_vector_equals((LHS)->annot[0], (RHS)->annot[0]))                                          \
)

#define cowl_axiom_annot_iterate_primitives(AXIOM, FLAGS, ITER)                                     \
    (!cowl_axiom_has_annot(AXIOM) ||                                                                \
     cowl_vector_iterate_primitives((AXIOM)->annot[0], FLAGS, ITER))

COWL_END_DECLS

#endif // COWL_AXIOM_PRIVATE_H
