/**
 * Defines CowlParser and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_H
#define COWL_PARSER_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlParserCtx);
/// @endcond

/// Defines a parser.
typedef struct CowlParser {

    /// Name of the parser.
    char const *name;

    /**
     * Pointer to a function that allocates the parser's state and reserves any needed resource.
     *
     * @return Parser state.
     *
     * @note This member is optional.
     */
    void* (*alloc)(void);

    /**
     * Pointer to a function that deallocates the parser's state and releases reserved resources.
     *
     * @param state Parser state.
     *
     * @note This member is optional.
     */
    void (*free)(void *state);

    /**
     * Pointer to a function that parses an ontology from an input stream.
     *
     * @param state Parser state.
     * @param stream Input stream.
     * @param ctx Parser context.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*parse)(void *state, UIStream *stream, CowlParserCtx *ctx);

    /**
     * Pointer to a function that returns the current line in the input stream, if applicable.
     *
     * @param state Parser state.
     * @return Current line.
     *
     * @note This member is optional.
     */
    ulib_uint (*get_line)(void *state);

} CowlParser;

#ifdef COWL_PARSER_FUNCTIONAL

/**
 * Returns the functional syntax parser.
 *
 * @return Functional syntax parser.
 *
 * @public @related CowlParser
 */
COWL_PUBLIC
CowlParser cowl_parser_get_functional(void);

#endif // COWL_PARSER_FUNCTIONAL

COWL_END_DECLS

#endif // COWL_PARSER_H
