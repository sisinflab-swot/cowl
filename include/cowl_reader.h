/**
 * Defines CowlReader and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_H
#define COWL_READER_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlStream);
/// @endcond

/// Defines a reader.
typedef struct CowlReader {

    /// Name of the reader.
    char const *name;

    /**
     * Pointer to a function that allocates the reader's state and reserves any needed resource.
     *
     * @return Reader state.
     *
     * @note This member is optional.
     */
    void *(*alloc)(void);

    /**
     * Pointer to a function that deallocates the reader's state and releases reserved resources.
     *
     * @param state Reader state.
     *
     * @note This member is optional.
     */
    void (*free)(void *state);

    /**
     * Pointer to a function that reads an ontology from an input stream.
     *
     * @param state Reader state.
     * @param istream Input stream.
     * @param stream Ontology stream.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*read)(void *state, UIStream *istream, CowlStream *stream);

} CowlReader;

#ifdef COWL_READER_FUNCTIONAL

/**
 * Returns the functional syntax reader.
 *
 * @return Functional syntax reader.
 *
 * @public @related CowlReader
 */
COWL_PUBLIC
CowlReader cowl_reader_functional(void);

#endif // COWL_READER_FUNCTIONAL

COWL_END_DECLS

#endif // COWL_READER_H
