/**
 * Defines CowlOWLVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
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

/// Vocabulary of OWL IRIs.
typedef struct CowlOWLIRIVocab {

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

} CowlOWLIRIVocab;

/// Vocabulary of OWL classes.
typedef struct CowlOWLClassVocab {

    /// owl:Thing
    CowlClass *thing;

    /// owl:Nothing
    CowlClass *nothing;

} CowlOWLClassVocab;

/// Vocabulary of OWL datatypes.
typedef struct CowlOWLDatatypeVocab {

    /// owl:rational
    CowlDatatype *rational;

    /// owl:real
    CowlDatatype *real;

} CowlOWLDatatypeVocab;

/// Vocabulary of OWL object properties.
typedef struct CowlOWLObjPropVocab {

    /// owl:topObjectProperty
    CowlObjProp *top_obj_prop;

    /// owl:bottomObjectProperty
    CowlObjProp *bottom_obj_prop;

} CowlOWLObjPropVocab;

/// Vocabulary of OWL data properties.
typedef struct CowlOWLDataPropVocab {

    /// owl:topDataProperty
    CowlDataProp *top_data_prop;

    /// owl:bottomDataProperty
    CowlDataProp *bottom_data_prop;

} CowlOWLDataPropVocab;

/// Vocabulary of OWL annotation properties.
typedef struct CowlOWLAnnotPropVocab {

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

} CowlOWLAnnotPropVocab;

/// The OWL 2 vocabulary.
typedef struct CowlOWLVocab {

    /// OWL namespace.
    CowlString *ns;

    /// IRIs sub-vocabulary.
    CowlOWLIRIVocab iri;

    /// Classes sub-vocabulary.
    CowlOWLClassVocab cls;

    /// Datatypes sub-vocabulary.
    CowlOWLDatatypeVocab dt;

    /// Object properties sub-vocabulary.
    CowlOWLObjPropVocab obj_prop;

    /// Data properties sub-vocabulary.
    CowlOWLDataPropVocab data_prop;

    /// Annotation properties sub-vocabulary.
    CowlOWLAnnotPropVocab annot_prop;

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
