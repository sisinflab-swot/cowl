/**
 * Defines the iterator API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_primitive_flags.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
uvec_decl(CowlObjectPtr);
uhash_decl(CowlObjectTable);
/// @endcond

/**
 * Iterator API.
 *
 * A @type{#CowlIterator} is a wrapper around a function that gets called for every element
 * matched by a query. The context provided while creating the iterator is passed to the
 * `for_each` function each time it is called.
 *
 * The iterator function returns a @type{bool} that can be used to control iteration: by returning
 * true iteration proceeds to the next element, while returning false causes it to stop.
 */
typedef struct CowlIterator {

    /// The iterator context, can be anything.
    void *ctx;

    /// Pointer to a function called by the iterator for every element.
    bool (*for_each)(void *ctx, CowlAny *object);

} CowlIterator;

/**
 * @defgroup CowlIterator CowlIterator API
 * @{
 */

/**
 * Initializes an iterator that stores objects in the specified vector.
 *
 * @param[out] vec Vector.
 * @param retain If true, elements are retained.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 */
COWL_API
CowlIterator cowl_iterator_vec(UVec(CowlObjectPtr) *vec, bool retain);

/**
 * Initializes an iterator that stores objects in the specified set.
 *
 * @param[out] set Set.
 * @param retain If true, elements are retained.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 */
COWL_API
CowlIterator cowl_iterator_set(UHash(CowlObjectTable) *set, bool retain);

/**
 * Initializes an iterator that counts the objects it iterates on.
 *
 * @param[out] count Object count.
 * @return Initialized iterator.
 */
COWL_API
CowlIterator cowl_iterator_count(ulib_uint *count);

/**
 * Initializes an iterator that checks if any of the objects it iterates on
 * is equal to the specified object.
 *
 * @param object The object to look for.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false if the element has been found.
 */
COWL_API
CowlIterator cowl_iterator_contains(CowlAny *object);

/// @}

COWL_END_DECLS

#endif // COWL_ITERATOR_H
