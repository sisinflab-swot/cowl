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

#include "cowl_attrs.h"
#include "cowl_macros.h"

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

    /// rdf:langString
    CowlIRI *lang_string;

    /// rdf:PlainLiteral
    CowlIRI *plain_literal;

    /// rdf:XMLLiteral
    CowlIRI *xml_literal;

} CowlRDFIRIVocab;

/// Vocabulary of RDF datatypes.
typedef struct CowlRDFDatatypeVocab {

    /// rdf:langString
    CowlDatatype *lang_string;

    /// rdf:PlainLiteral
    CowlDatatype *plain_literal;

    /// rdf:XMLLiteral
    CowlDatatype *xml_literal;

} CowlRDFDatatypeVocab;

/// The RDF vocabulary.
typedef struct CowlRDFVocab {

    /// RDF namespace.
    CowlString *ns;

    /// RDF prefix.
    CowlString *prefix;

    /// IRIs sub-vocabulary.
    CowlRDFIRIVocab iri;

    /// Datatypes sub-vocabulary.
    CowlRDFDatatypeVocab dt;

} CowlRDFVocab;

/**
 * Returns the RDF vocabulary.
 *
 * @return The RDF vocabulary.
 */
COWL_API
COWL_CONST
CowlRDFVocab const *cowl_rdf_vocab(void);

COWL_END_DECLS

#endif // COWL_RDF_VOCAB_H
