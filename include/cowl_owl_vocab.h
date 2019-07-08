/**
 * Defines CowlOWLVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OWL_VOCAB_H
#define COWL_OWL_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlString);
/// @endcond

/// The OWL 2 vocabulary.
typedef cowl_struct(CowlOWLVocab) {

    /// OWL namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// owl:backwardCompatibleWith
        CowlIRI *backward_comp;

        /// owl:bottomDataProperty
        CowlIRI *bottom_data_prop;

        /// owl:bottomObjectProperty
        CowlIRI *bottom_obj_prop;

        /// owl:deprecated
        CowlIRI *deprecated;

        /// owl:incompatibleWith
        CowlIRI *incompatible;

        /// owl:Nothing
        CowlIRI *nothing;

        /// owl:priorVersion
        CowlIRI *prior_version;

        /// owl:rational
        CowlIRI *rational;

        /// owl:real
        CowlIRI *real;

        /// owl:version_info
        CowlIRI *version_info;

        /// owl:Thing
        CowlIRI *thing;

        /// owl:topDataProperty
        CowlIRI *top_data_prop;

        /// owl:topObjectProperty
        CowlIRI *top_obj_prop;

    } iri;

    /// Classes.
    struct {

        /// owl:Thing
        CowlClass *thing;

        /// owl:Nothing
        CowlClass *nothing;

    } cls;

    /// Datatypes
    struct {

        /// owl:rational
        CowlDatatype *rational;

        /// owl:real
        CowlDatatype *real;

    } dt;

    /// Object properties.
    struct {

        /// owl:topObjectProperty
        CowlObjProp *top_obj_prop;

        /// owl:bottomObjectProperty
        CowlObjProp *bottom_obj_prop;

    } obj_props;

    /// Data properties.
    struct {

        /// owl:topDataProperty
        CowlDataProp *top_data_prop;

        /// owl:bottomDataProperty
        CowlDataProp *bottom_data_prop;

    } data_props;

    /// Annotation properties.
    struct {

        /// owl:backwardCompatibleWith
        CowlAnnotProp *backward_comp;

        /// owl:deprecated
        CowlAnnotProp *deprecated;

        /// owl:incompatibleWith
        CowlAnnotProp *incompatible;

        /// owl:priorVersion
        CowlAnnotProp *prior_version;

        /// owl:version_info
        CowlAnnotProp *version_info;

    } annot_props;

} const CowlOWLVocab;

/**
 * Gets the OWL 2 vocabulary.
 *
 * @return The OWL 2 vocabulary.
 *
 * @public @memberof CowlOWLVocab
 */
COWL_PUBLIC
CowlOWLVocab* cowl_owl_vocab_get(void);

COWL_END_DECLS

#endif // COWL_OWL_VOCAB_H
