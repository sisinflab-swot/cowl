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
#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlOntology);
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
 *
 * @note This is not a real data structure, though it is declared as such
 *       for better grouping in the generated documentation.
 *
 * @struct CowlIterator
 */

/**
 * Defines a new iterator type.
 *
 * @param T Element base type.
 * @param PTR * for iterators to pointer elements, empty otherwise.
 *
 * @note Under normal circumstances you don't need to use this.
 *       It's used in the CowlIterator header to generate
 *       the concrete iterator types used throughout the API.
 *
 * @private @related CowlIterator
 */
#define COWL_ITERATOR_DEF(T, PTR)                                                                   \
    /** T PTR iterator. */                                                                          \
    /** @extends CowlIterator */                                                                    \
    typedef cowl_struct(T##Iterator) {                                                              \
        /** The iterator context, can be anything. */                                               \
        void *ctx;                                                                                  \
        /** Pointer to a function called by the iterator for every element. */                      \
        bool (*for_each)(void *ctx, T PTR elem);                                                    \
    } const T##Iterator

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
    { .ctx = (void *)(CTX), .for_each = (FOR_EACH) }

COWL_ITERATOR_DEF(CowlEntity, );
COWL_ITERATOR_DEF(CowlAxiom, *);
COWL_ITERATOR_DEF(CowlClsExp, *);
COWL_ITERATOR_DEF(CowlDataPropExp, *);
COWL_ITERATOR_DEF(CowlObjPropExp, *);
COWL_ITERATOR_DEF(CowlIndividual, *);
COWL_ITERATOR_DEF(CowlOntology, *);
COWL_ITERATOR_DEF(CowlAnnotProp, *);
COWL_ITERATOR_DEF(CowlClass, *);
COWL_ITERATOR_DEF(CowlDataProp, *);
COWL_ITERATOR_DEF(CowlDatatype, *);
COWL_ITERATOR_DEF(CowlObjProp, *);
COWL_ITERATOR_DEF(CowlNamedInd, *);
COWL_ITERATOR_DEF(CowlAnonInd, *);
COWL_ITERATOR_DEF(CowlAnnotation, *);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
