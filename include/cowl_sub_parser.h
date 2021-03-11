/**
 * Defines CowlSubParser and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_PARSER_H
#define COWL_SUB_PARSER_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlParserCtx);
/// @endcond

/// Defines a subparser.
typedef cowl_struct(CowlSubParser) {

    /// Name of the subparser.
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
     * @param ctx Parser context.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*parse)(void *state, CowlParserCtx *ctx);

    /**
     * Pointer to a function that returns the current line in the input stream, if applicable.
     *
     * @param state Parser state.
     * @return Current line.
     *
     * @note This member is optional.
     */
    cowl_uint (*get_line)(void *state);

} CowlSubParser;

#ifdef COWL_PARSER_FUNCTIONAL

/**
 * Functional subparser.
 *
 * @public @related CowlSubParser
 */
COWL_PUBLIC
extern CowlSubParser const *const cowl_func_parser;

#endif // COWL_PARSER_FUNCTIONAL

COWL_END_DECLS

#endif // COWL_SUB_PARSER_H
