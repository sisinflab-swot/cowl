/**
 * Declares CowlVector and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
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
typedef CowlAny *CowlObjectPtr;
UVEC_DECL_EQUATABLE_SPEC(CowlObjectPtr, COWL_PUBLIC)
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Vector of #CowlObject elements.
 *
 * @struct CowlVector
 * @extends CowlObject
 */

/**
 * Returns a retained vector.
 *
 * @param vec Underlying raw vector.
 * @return Retained vector, or NULL on error.
 *
 * @note You must not use the raw vector after passing it to this function.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
CowlVector *cowl_vector(UVec(CowlObjectPtr) *vec);

/**
 * Returns a retained vector with no elements.
 *
 * @return [CowlVector*] Retained vector, or NULL on error.
 *
 * @public @related CowlVector
 */
#define cowl_vector_empty() cowl_vector(NULL)

/**
 * Returns the underlying raw vector.
 *
 * @param vec The vector.
 * @return Underlying raw vector.
 *
 * @public @memberof CowlVector
 */
COWL_PUBLIC
UVec(CowlObjectPtr) const *cowl_vector_get_data(CowlVector *vec);

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
 * Returns the number of elements in the vector.
 *
 * @param vec The vector.
 * @return Number of elements in the vector.
 *
 * @public @related CowlVector
 */
COWL_INLINE
ulib_uint cowl_vector_count(CowlVector *vec) {
    return uvec_count(CowlObjectPtr, cowl_vector_get_data(vec));
}

/**
 * Returns the element at the specified index.
 *
 * @param vec The vector.
 * @param idx The index.
 * @return The element at the specified index.
 *
 * @public @related CowlVector
 */
COWL_INLINE
CowlAny *cowl_vector_get_item(CowlVector *vec, ulib_uint idx) {
    return uvec_get(CowlObjectPtr, cowl_vector_get_data(vec), idx);
}

/**
 * Iterates over the vector, executing the specified code block for each element.
 *
 * @param vec [CowlVector *] The vector.
 * @param obj [symbol] Name of the variable holding the current item and its index.
 *
 * @public @related CowlVector
 */
#define cowl_vector_foreach(vec, obj) uvec_foreach (CowlObjectPtr, cowl_vector_get_data(vec), obj)

COWL_END_DECLS

#endif // COWL_VECTOR_H
