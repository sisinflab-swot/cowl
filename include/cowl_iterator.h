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
 * A CowlIterator is a wrapper around a function that gets called for every element
 * matched by a query submitted to a CowlOntology. By providing a generic context pointer,
 * you can plug any data structure (loggers, collections, etc.) which allows
 * for arbitrarily complex programmatic queries.
 *
 * The iterator function returns a `boolean` that can be used to control iteration:
 * by returning `true` iteration proceeds to the next element,
 * while returning `false` causes it to stop. This is useful if, for example,
 * you want to find the first element matching certain criteria.
 */
typedef struct CowlIterator {

    /// The iterator context, can be anything.
    void *ctx;

    /// Pointer to a function called by the iterator for every element.
    bool (*for_each)(void *ctx, CowlAny *object);

} CowlIterator;

/**
 * Initializes an iterator that stores objects in the specified vector.
 *
 * @param[out] vec Vector.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_vec(UVec(CowlObjectPtr) *vec);

/**
 * Initializes an iterator that stores objects in the specified set.
 *
 * @param[out] set Set.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_set(UHash(CowlObjectTable) *set);

/**
 * Initializes an iterator that counts the objects it iterates on.
 *
 * @param[out] count Object count.
 * @return Initialized iterator.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_count(ulib_uint *count);

/**
 * Initializes an iterator that checks if any of the objects it iterates on
 * is equal to the specified object.
 *
 * @param object The object to look for.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false if the element has been found.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_contains(CowlAny *object);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
