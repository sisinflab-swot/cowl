/**
 * Defines CowlRDFSVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RDFS_VOCAB_H
#define COWL_RDFS_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// The RDFS vocabulary.
typedef cowl_struct(CowlRDFSVocab) {

    /// RDFS namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// rdfs:comment
        CowlIRI *comment;

        /// rdfs:isDefinedBy
        CowlIRI *defined_by;

        /// rdfs:label
        CowlIRI *label;

        /// rdfs:Literal
        CowlIRI *literal;

        /// rdfs:seeAlso
        CowlIRI *see_also;

    } iri;

    /// Datatypes.
    struct {

        /// rdfs:Literal
        CowlDatatype *literal;

    } dt;

    /// Annotation properties.
    struct {

        /// rdfs:comment
        CowlAnnotProp *comment;

        /// rdfs:isDefinedBy
        CowlAnnotProp *defined_by;

        /// rdfs:label
        CowlAnnotProp *label;

        /// rdfs:seeAlso
        CowlAnnotProp *see_also;

    } annot_props;

} const CowlRDFSVocab;

/**
 * Gets the RDFS vocabulary.
 *
 * @return The RDFS vocabulary.
 *
 * @public @memberof CowlRDFSVocab
 */
COWL_PUBLIC
CowlRDFSVocab* cowl_rdfs_vocab_get(void);

COWL_END_DECLS

#endif // COWL_RDFS_VOCAB_H
