/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CHANGE_HANDLER_H
#define COWL_CHANGE_HANDLER_H

#include "cowl_attrs.h"
#include "cowl_change.h" // IWYU pragma: export
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/// Change handler.
typedef struct CowlChangeHandler {

    /// Context, can be anything.
    void *ctx;

    /**
     * Pointer to a function that handles the specified change.
     *
     * @param ctx Context.
     * @param change Change.
     * @return Return code.
     */
    cowl_ret (*handle)(void *ctx, CowlChange change);

} CowlChangeHandler;

/**
 * @defgroup CowlChangeHandler CowlChangeHandler API
 * @{
 */

/**
 * Handles the specified change.
 *
 * @param handler Change handler.
 * @param change Change.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_change_handler_handle(CowlChangeHandler *handler, CowlChange change) {
    return handler->handle(handler->ctx, change);
}

/**
 * Initializes a change handler that modifies the specified ontology.
 *
 * @param onto Ontology.
 * @return Change handler.
 */
COWL_API
COWL_CONST
CowlChangeHandler cowl_change_handler_to_ontology(CowlOntology *onto);

/**
 * Processes the specified ontology as changes of the specified type.
 *
 * @param handler Change handler.
 * @param onto Ontology.
 * @param type Change type.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_change_handler_handle_ontology(CowlChangeHandler *handler, CowlOntology *onto,
                                             cowl_change_type type);

/// @}

COWL_END_DECLS

#endif // COWL_CHANGE_HANDLER_H
