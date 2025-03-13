/**
 * Defines CowlXMLVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_XML_VOCAB_H
#define COWL_XML_VOCAB_H

#include "cowl_attrs.h"
#include "cowl_utils.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/// The XML vocabulary.
typedef struct CowlXMLVocab {

    /// XML namespace.
    CowlString *ns;

    /// XML prefix.
    CowlString *prefix;

    /// xmlns namespace.
    CowlString *xmlns_ns;

    /// xmlns prefix.
    CowlString *xmlns_prefix;

} CowlXMLVocab;

/**
 * Returns the XML vocabulary.
 *
 * @return The XML vocabulary.
 */
COWL_API
COWL_CONST
CowlXMLVocab const *cowl_xml_vocab(void);

COWL_END_DECLS

#endif // COWL_XML_VOCAB_H
