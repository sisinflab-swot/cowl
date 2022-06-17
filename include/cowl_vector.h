/**
 * Declares CowlVector and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VECTOR_H
#define COWL_VECTOR_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
typedef void* CowlObjectPtr;
UVEC_DECL_EQUATABLE_SPEC(CowlObjectPtr, COWL_PUBLIC)
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Vector of CowlObject* elements.
 *
 * @struct CowlVector
 * @extends CowlObject
 */

/**
 * Returns a retained vector.
 * The equality and hash functions of the vector do not account for the order of its elements.
 *
 * @param vec Underlying raw vector.
 * @return Retained vector, or NULL on error.
 *
 * @note You must not use the raw vector after passing it to this function.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
CowlVector* cowl_vector_get(UVec(CowlObjectPtr) *vec);

/**
 * Returns a retained vector.
 * The equality and hash functions of the vector account for the order of its elements.
 *
 * @param vec Underlying raw vector.
 * @return Retained vector, or NULL on error.
 *
 * @note You must not use the raw vector after passing it to this function.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
CowlVector* cowl_vector_ordered_get(UVec(CowlObjectPtr) *vec);

/**
 * Returns a retained vector with no elements.
 *
 * @return [CowlVector*] Retained vector, or NULL on error.
 *
 * @public @related CowlVector
 */
#define cowl_vector_empty_get() cowl_vector_get(NULL)

/**
 * Returns a retained vector with no elements.
 * The equality and hash functions of the vector account for the order of its elements.
 *
 * @return [CowlVector*] Retained vector, or NULL on error.
 *
 * @public @related CowlVector
 */
#define cowl_vector_ordered_empty_get() cowl_vector_ordered_get(NULL)

/**
 * Retains the specified vector.
 *
 * @param vec The vector.
 * @return Retained vector.
 *
 * @public @memberof CowlVector
 */
COWL_INLINE
CowlVector* cowl_vector_retain(CowlVector *vec) {
    return (CowlVector *)cowl_retain(vec);
}

/**
 * Releases the specified vector.
 *
 * @param vec The vector.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
void cowl_vector_release(CowlVector *vec);

/**
 * Returns the underlying raw vector.
 *
 * @param vec The vector.
 * @return Underlying raw vector.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
UVec(CowlObjectPtr) const* cowl_vector_get_data(CowlVector *vec);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
bool cowl_vector_equals(CowlVector *lhs, CowlVector *rhs);

/**
 * Hash function.
 *
 * @param vec The vector.
 * @return The hash value.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
ulib_uint cowl_vector_hash(CowlVector *vec);

/**
 * Iterates over the primitives referenced by the specified vector.
 *
 * @param vec The vector.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
bool cowl_vector_iterate_primitives(CowlVector *vec, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Returns the number of elements in the vector.
 *
 * @param vec [CowlVector *] The vector.
 * @return [ulib_uint] Number of elements in the vector.
 *
 * @public @related CowlVector
 */
#define cowl_vector_count(vec) uvec_count(CowlObjectPtr, cowl_vector_get_data(vec))

/**
 * Iterates over the vector, executing the specified code block for each element.
 *
 * @param vec [CowlVector *] The vector.
 * @param obj [symbol] Name of the variable holding the current item and its index.
 *
 * @public @related CowlVector
 */
#define cowl_vector_foreach(vec, obj) uvec_foreach(CowlObjectPtr, cowl_vector_get_data(vec), obj)

COWL_END_DECLS

#endif // COWL_VECTOR_H
