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

#include "cowl_attrs.h"
#include "cowl_macros.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIStream);
/// @endcond

/// Defines a reader.
typedef struct CowlReader {

    /// Name of the reader.
    char const *name;

    /**
     * Pointer to a function that reads an ontology from an input stream.
     *
     * @param state Reader state.
     * @param istream Input stream.
     * @param stream Ontology input stream.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*read)(UIStream *istream, CowlIStream *stream);

} CowlReader;

/**
 * @defgroup CowlReader CowlReader API
 * @{
 */

#ifdef COWL_READER_FUNCTIONAL

/**
 * Returns the functional syntax reader.
 *
 * @return Functional syntax reader.
 */
COWL_API
COWL_CONST
CowlReader cowl_reader_functional(void);

#endif // COWL_READER_FUNCTIONAL

/// @}

COWL_END_DECLS

#endif // COWL_READER_H
