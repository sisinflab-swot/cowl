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

#include "cowl_std.h"
#include "cowl_primitive_flags.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObject);
cowl_hash_decl(CowlObjectTable);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
/// @endcond

/**
 * Iterator API.
 *
 * A CowlIterator is a wrapper around a function that gets called for every element
 * matched by a query submitted to a CowlOntology. By providing a generic context pointer,
 * you can plug any data structure (loggers, collections, etc.) which allows
 * for arbitrarily complex queries.
 *
 * The iterator function returns a `boolean` that can be used to control iteration:
 * by returning `true` iteration goes on to the next element,
 * while returning `false` causes it to stop. This is useful if, for example,
 * you want to find the first element matching certain criteria.
 */
typedef struct CowlIterator {

    /// The iterator context, can be anything.
    void *ctx;

    /// Pointer to a function called by the iterator for every element.
    bool (*for_each)(void *ctx, void *object);

} CowlIterator;

/**
 * Initializes an iterator.
 *
 * @param CTX Iterator context, can be anything.
 * @param FOR_EACH Pointer to a function called by the iterator for every element.
 * @return Initialized iterator.
 *
 * @public @related CowlIterator
 */
#define cowl_iterator_init(CTX, FOR_EACH) \
    ((CowlIterator){ .ctx = (void *)(CTX), .for_each = (FOR_EACH) })

/**
 * Initializes an iterator that stores objects in the specified vector.
 *
 * @param vec Vector.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 * @note If vec is NULL, a new vector is allocated and assigned to the iterator context.
 *       You are responsible for deallocating it and releasing its elements.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_vec_init(UVec(CowlObjectPtr) *vec);

/**
 * Initializes an iterator that stores objects in the specified set.
 *
 * @param set Set.
 * @return Initialized iterator.
 *
 * @note When using this iterator, iterator functions return false on error,
 *       e.g. when memory cannot be allocated.
 * @note If set is NULL, a new set is allocated and assigned to the iterator context.
 *       You are responsible for deallocating it and releasing its elements.
 *
 * @public @related CowlIterator
 */
COWL_PUBLIC
CowlIterator cowl_iterator_set_init(UHash(CowlObjectTable) *set);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
