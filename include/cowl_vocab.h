/**
 * Defines CowlOWLVocab, CowlRDFVocab and CowlXSDVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VOCAB_H
#define COWL_VOCAB_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// The OWL 2 vocabulary.
typedef cowl_struct(CowlOWLVocab) {

    /// OWL namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// owl:Thing
        CowlIRI *thing;

        /// owl:Nothing
        CowlIRI *nothing;

    } iri;

    /// Classes.
    struct {

        /// owl:Thing
        CowlClass *thing;

        /// owl:Nothing
        CowlClass *nothing;

    } cls;

} const CowlOWLVocab;

/// The RDF vocabulary.
typedef cowl_struct(CowlRDFVocab) {

    /// RDF namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// rdf:PlainLiteral
        CowlIRI *plain_literal;

    } iri;

    /// Datatypes.
    struct {

        /// rdf:PlainLiteral
        CowlDatatype *plain_literal;

    } dt;

} const CowlRDFVocab;

/// The XSD vocabulary.
typedef cowl_struct(CowlXSDVocab) {

    /// XSD namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// xsd:length
        CowlIRI *length;

        /// xsd:minLength
        CowlIRI *min_length;

        /// xsd:maxLength
        CowlIRI *max_length;

        /// xsd:pattern
        CowlIRI *pattern;

        /// xsd:minInclusive
        CowlIRI *min_inclusive;

        /// xsd:minExclusive
        CowlIRI *min_exclusive;

        /// xsd:maxInclusive
        CowlIRI *max_inclusive;

        /// xsd:maxExclusive
        CowlIRI *max_exclusive;

        /// xsd:totalDigits
        CowlIRI *total_digits;

        /// xsd:fractionDigits
        CowlIRI *fraction_digits;

        /// xsd:langRange
        CowlIRI *lang_range;

    } iri;

} const CowlXSDVocab;

/**
 * Gets the OWL 2 vocabulary.
 *
 * @return The OWL 2 vocabulary.
 *
 * @public @memberof CowlOWLVocab
 */
COWL_PUBLIC
CowlOWLVocab* cowl_owl_vocab_get(void);

/**
 * Gets the RDF vocabulary.
 *
 * @return The RDF vocabulary.
 *
 * @public @memberof CowlRDFVocab
 */
COWL_PUBLIC
CowlRDFVocab* cowl_rdf_vocab_get(void);

/**
 * Gets the XSD vocabulary.
 *
 * @return The XSD vocabulary.
 *
 * @public @memberof CowlXSDVocab
 */
COWL_PUBLIC
CowlXSDVocab* cowl_xsd_vocab_get(void);

COWL_END_DECLS

#endif // COWL_VOCAB_H
