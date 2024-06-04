/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VECTOR_PRIVATE_H
#define COWL_VECTOR_PRIVATE_H

#include "cowl_object_private.h"
#include "cowl_ret.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

struct CowlVector {
    CowlObject super;
    UVec(CowlObjectPtr) data;
};

#define cowl_vector_is_ordered(vec) cowl_object_bit_get(vec)
#define cowl_vector_set_ordered(vec) cowl_object_bit_set(vec)

CowlVector *cowl_vector_ordered_empty(void);
void cowl_vector_free(CowlVector *vec);
void cowl_vector_release_ex(CowlVector *vec, bool release_elements);
cowl_ret cowl_vector_add(CowlVector *vec, CowlAny *object);
cowl_ret cowl_vector_push(CowlVector *vec, CowlAny *object);
bool cowl_vector_remove(CowlVector *vec, CowlAny *object);
cowl_ret cowl_vector_shrink(CowlVector *vec);
COWL_PURE bool cowl_vector_equals(CowlVector *lhs, CowlVector *rhs);
COWL_PURE ulib_uint cowl_vector_hash(CowlVector *vec);
bool cowl_vector_iterate_primitives(CowlVector *vec, CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_VECTOR_PRIVATE_H
