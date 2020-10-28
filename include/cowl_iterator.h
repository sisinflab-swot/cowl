/**
 * Defines the iterator API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObject);
/// @endcond

/// Iterator flags, used to control iteration.
typedef CowlFlags(8) CowlIteratorFlags;

/// All flags off.
#define COWL_IF_NONE        cowl_flags_empty

/// All flags on.
#define COWL_IF_ALL         ((CowlIteratorFlags)-1)

/// Iterate over classes.
#define COWL_IF_CLASS       cowl_flags_bit(0)

/// Iterate over object properties.
#define COWL_IF_OBJ_PROP    cowl_flags_bit(1)

/// Iterate over data properties.
#define COWL_IF_DATA_PROP   cowl_flags_bit(2)

/// Iterate over annotation properties.
#define COWL_IF_ANNOT_PROP  cowl_flags_bit(3)

/// Iterate over named individuals.
#define COWL_IF_NAMED_IND   cowl_flags_bit(4)

/// Iterate over anonymous individuals.
#define COWL_IF_ANON_IND    cowl_flags_bit(5)

/// Iterate over datatypes.
#define COWL_IF_DATATYPE    cowl_flags_bit(6)

/// Iterate over entities.
#define COWL_IF_ENTITY      (COWL_IF_CLASS | COWL_IF_OBJ_PROP | COWL_IF_DATA_PROP | \
                             COWL_IF_ANNOT_PROP | COWL_IF_NAMED_IND | COWL_IF_DATATYPE)

/// Iterate over primitives, a collective term for entities and anonymous individuals.
#define COWL_IF_PRIMITIVE   (COWL_IF_ENTITY | COWL_IF_ANON_IND)

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
typedef cowl_struct(CowlIterator) {

    /// Iterator flags.
    CowlIteratorFlags flags;

    /// The iterator context, can be anything.
    void *ctx;

    /// Pointer to a function called by the iterator for every element.
    bool (*for_each)(void *ctx, void *object);

} CowlIterator;

/**
 * Initializes an iterator.
 *
 * @param FLAGS Iterator flags.
 * @param CTX Iterator context, can be anything.
 * @param FOR_EACH Pointer to a function called by the iterator for every element.
 * @return Initialized iterator.
 *
 * @public @related CowlIterator
 */
#define cowl_iterator_init_ex(FLAGS, CTX, FOR_EACH) \
    ((CowlIterator){ .flags = (FLAGS), .ctx = (void *)(CTX), .for_each = (FOR_EACH) })

/**
 * Initializes an iterator.
 *
 * @param CTX Iterator context, can be anything.
 * @param FOR_EACH Pointer to a function called by the iterator for every element.
 * @return Initialized iterator.
 *
 * @public @related CowlIterator
 */
#define cowl_iterator_init(CTX, FOR_EACH) cowl_iterator_init_ex(COWL_IF_ALL, CTX, FOR_EACH)

COWL_END_DECLS

#endif // COWL_ITERATOR_H
