/**
 * Defines CowlRDFVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
