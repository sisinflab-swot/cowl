/**
 * Defines CowlRDFVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RDF_VOCAB_H
#define COWL_RDF_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// Vocabulary of RDF IRIs.
typedef struct CowlRDFIRIVocab {

    /// rdf:langRange
    CowlIRI *lang_range;

    /// rdf:PlainLiteral
    CowlIRI *plain_literal;

    /// rdf:XMLLiteral
    CowlIRI *xml_literal;

} CowlRDFIRIVocab;

/// Vocabulary of RDF datatypes.
typedef struct CowlRDFDatatypeVocab {

    /// rdf:PlainLiteral
    CowlDatatype *plain_literal;

    /// rdf:XMLLiteral
    CowlDatatype *xml_literal;

} CowlRDFDatatypeVocab;

/// The RDF vocabulary.
typedef struct CowlRDFVocab {

    /// RDF namespace.
    CowlString *ns;

    /// IRIs sub-vocabulary.
    CowlRDFIRIVocab iri;

    /// Datatypes sub-vocabulary.
    CowlRDFDatatypeVocab dt;

} const CowlRDFVocab;

/**
 * Gets the RDF vocabulary.
 *
 * @return The RDF vocabulary.
 *
 * @public @memberof CowlRDFVocab
 */
COWL_PUBLIC
CowlRDFVocab* cowl_rdf_vocab_get(void);

COWL_END_DECLS

#endif // COWL_RDF_VOCAB_H
