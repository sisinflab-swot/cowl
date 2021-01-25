/**
 * Declares CowlObjectVec and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_VEC_H
#define COWL_OBJECT_VEC_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
typedef void* CowlObjectPtr;
UVEC_DECL_EQUATABLE_SPEC(CowlObjectPtr, COWL_PUBLIC)
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
/// @endcond

/**
 * Vector of CowlObject * elements.
 *
 * @struct CowlObjectVec
 * @extends Vector
 */

/**
 * Deallocates the specified vector, releasing its elements.
 *
 * @param vec The vector.
 *
 * @public @memberof CowlObjectVec
 */
COWL_PUBLIC
void cowl_object_vec_free(CowlObjectVec *vec);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjectVec
 */
COWL_PUBLIC
bool cowl_object_vec_equals(CowlObjectVec *lhs, CowlObjectVec *rhs);

/**
 * Hash function.
 *
 * @param vec The vector.
 * @return The hash value.
 *
 * @public @memberof CowlObjectVec
 */
COWL_PUBLIC
cowl_uint cowl_object_vec_hash(CowlObjectVec *vec);

/**
 * Iterates over the primitives referenced by the specified vector.
 *
 * @param vec The vector.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjectVec
 */
COWL_PUBLIC
bool cowl_object_vec_iterate_primitives(CowlObjectVec *vec, CowlIterator *iter,
                                        CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_OBJECT_VEC_H
