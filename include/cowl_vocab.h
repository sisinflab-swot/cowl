/**
 * Defines CowlVocab and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VOCAB_H
#define COWL_VOCAB_H

#include "cowl_entity.h"
#include "cowl_iri.h"

// IWYU pragma: begin_exports
#include "cowl_owl_vocab.h"
#include "cowl_rdf_vocab.h"
#include "cowl_rdfs_vocab.h"
#include "cowl_xsd_vocab.h"
// IWYU pragma: end_exports

COWL_BEGIN_DECLS

/// Vocabulary of reserved terms.
typedef struct CowlVocab {

    /// OWL vocabulary.
    CowlOWLVocab const *owl;

    /// RDF vocabulary.
    CowlRDFVocab const *rdf;

    /// RDFS vocabulary.
    CowlRDFSVocab const *rdfs;

    /// XSD vocabulary.
    CowlXSDVocab const *xsd;

} CowlVocab;

/**
 * @defgroup CowlVocab CowlVocab API
 * @{
 */

/**
 * Returns the vocabulary of reserved terms.
 *
 * @return Vocabulary of reserved terms.
 */
COWL_API
COWL_CONST
CowlVocab const *cowl_vocab(void);

/**
 * Checks whether the specified prefix is in the reserved vocabulary.
 *
 * @param prefix The prefix.
 * @return True if the prefix is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_vocab_is_reserved_prefix(CowlString *prefix);

/**
 * Checks whether the specified namespace is in the reserved vocabulary.
 *
 * @param ns The namespace.
 * @return True if the namespace is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_vocab_is_reserved_ns(CowlString *ns);

/**
 * Checks whether the specified prefix is in the reserved vocabulary.
 *
 * @param prefix The prefix.
 * @return True if the prefix is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_vocab_is_reserved_prefix_raw(UString prefix);

/**
 * Checks whether the specified namespace is in the reserved vocabulary.
 *
 * @param ns The namespace.
 * @return True if the namespace is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_vocab_is_reserved_ns_raw(UString ns);

/// @}

COWL_END_DECLS

#endif // COWL_VOCAB_H
