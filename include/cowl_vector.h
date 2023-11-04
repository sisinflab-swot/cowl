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
UVEC_DECL_EQUATABLE_SPEC(CowlObjectPtr, COWL_API)
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * UVec of CowlObject elements.
 *
 * @struct UVec_CowlObjectPtr
 * @extends UVec
 */

/**
 * Vector of CowlObject elements.
 *
 * @struct CowlVector
 * @extends CowlObject
 */

/**
 * Returns a vector.
 *
 * @param vec Underlying raw vector.
 * @return Vector, or NULL on error.
 *
 * @note You must not use the raw vector after passing it to this function.
 * @note Elements in the raw vector are retained by this constructor.
 *
 * @public @memberof CowlVector
 */
COWL_API
COWL_RETAINED
CowlVector *cowl_vector(UVec(CowlObjectPtr) *vec);

/**
 * Returns a vector with no elements.
 *
 * @return [CowlVector*] Vector, or NULL on error.
 *
 * @public @related CowlVector
 */
COWL_RETAINED
#define cowl_vector_empty() cowl_vector(NULL)

/**
 * Returns the underlying raw vector.
 *
 * @param vec The vector.
 * @return Underlying raw vector.
 *
 * @public @memberof CowlVector
 */
COWL_API
UVec(CowlObjectPtr) const *cowl_vector_get_data(CowlVector *vec);

/**
 * Returns the number of elements in the vector.
 *
 * @param vec The vector.
 * @return Number of elements in the vector.
 *
 * @public @memberof CowlVector
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
 * @public @memberof CowlVector
 */
COWL_INLINE
CowlAny *cowl_vector_get_item(CowlVector *vec, ulib_uint idx) {
    return uvec_get(CowlObjectPtr, cowl_vector_get_data(vec), idx);
}

/**
 * Checks whether the vector contains the specified element.
 *
 * @param vec The vector.
 * @param object The object.
 * @return True if the vector contains the specified element, false otherwise.
 *
 * @public @memberof CowlVector
 */
COWL_INLINE
bool cowl_vector_contains(CowlVector *vec, CowlAny *object) {
    return uvec_contains(CowlObjectPtr, cowl_vector_get_data(vec), object);
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
