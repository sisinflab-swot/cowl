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

#include "cowl_any.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// Pointer to any @type{#CowlObject}.
typedef CowlAny *CowlObjectPtr;

/**
 * @func{#UVec(T)} of @type{#CowlObject *} elements.
 *
 * @alias typedef UVec(CowlObjectPtr) UVec(CowlObjectPtr);
 */

/// @cond
UVEC_DECL_EQUATABLE_SPEC(CowlObjectPtr, COWL_API)
/// @endcond

/**
 * Vector of @type{#CowlObject} elements.
 *
 * @superstruct{CowlObject}
 * @struct CowlVector
 */
cowl_struct_decl(CowlVector);

/**
 * @defgroup CowlVector CowlVector API
 * @{
 */

/**
 * Returns a vector.
 *
 * @param vec Underlying raw vector.
 * @return Vector, or NULL on error.
 *
 * @note You must not use the raw vector after passing it to this function.
 * @note Elements in the raw vector are retained by this constructor.
 */
COWL_API
COWL_RETAINED
CowlVector *cowl_vector(UVec(CowlObjectPtr) *vec);

/**
 * Returns a vector with no elements.
 *
 * @return Vector, or NULL on error.
 *
 * @alias COWL_RETAINED CowlVector *cowl_vector_empty(void);
 */
COWL_RETAINED
#define cowl_vector_empty() cowl_vector(NULL)

/**
 * Returns the underlying raw vector.
 *
 * @param vec The vector.
 * @return Underlying raw vector.
 */
COWL_API
COWL_PURE
UVec(CowlObjectPtr) const *cowl_vector_get_data(CowlVector *vec);

/**
 * Returns the number of elements in the vector.
 *
 * @param vec The vector.
 * @return Number of elements in the vector.
 */
COWL_PURE
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
 */
COWL_PURE
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
 */
COWL_PURE
COWL_INLINE
bool cowl_vector_contains(CowlVector *vec, CowlAny *object) {
    return uvec_contains(CowlObjectPtr, cowl_vector_get_data(vec), object);
}

/**
 * Iterates over the vector, executing the specified code block for each element.
 *
 * @param vec @type{#CowlVector *} The vector.
 * @param obj @type{symbol} Name of the variable holding the current item and its index.
 */
#define cowl_vector_foreach(vec, obj) uvec_foreach (CowlObjectPtr, cowl_vector_get_data(vec), obj)

/// @}

COWL_END_DECLS

#endif // COWL_VECTOR_H
