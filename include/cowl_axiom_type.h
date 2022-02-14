/**
 * Defines the #CowlAxiomType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_TYPE_H
#define COWL_AXIOM_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlAxiom.
typedef enum CowlAxiomType {

/// @name Declaration/definition

    /// CowlDeclAxiom - Declaration.
    COWL_AT_DECL,

    /// CowlDatatypeDefAxiom - Datatype definition.
    COWL_AT_DATATYPE_DEF,

/// @name Class axioms

    /// CowlSubClsAxiom - Subclass.
    COWL_AT_SUB_CLASS,

    /// CowlNAryClsAxiom - Equivalent classes.
    COWL_AT_EQUIV_CLASSES,

    /// CowlNAryClsAxiom - Disjoint classes.
    COWL_AT_DISJ_CLASSES,

    /// CowlDisjUnionAxiom - Disjoint union.
    COWL_AT_DISJ_UNION,

/// @name Individual axioms

    /// CowlClsAssertAxiom - Class assertion.
    COWL_AT_CLASS_ASSERT,

    /// CowlNAryIndAxiom - Same individual.
    COWL_AT_SAME_IND,

    /// CowlNAryIndAxiom - Different individuals.
    COWL_AT_DIFF_IND,

    /// CowlObjPropAssertAxiom - Object property assertion.
    COWL_AT_OBJ_PROP_ASSERT,

    /// CowlObjPropAssertAxiom - Negative object property assertion.
    COWL_AT_NEG_OBJ_PROP_ASSERT,

    /// CowlDataPropAssertAxiom - Data property assertion.
    COWL_AT_DATA_PROP_ASSERT,

    /// CowlDataPropAssertAxiom - Negative data property assertion.
    COWL_AT_NEG_DATA_PROP_ASSERT,

/// @name Object property axioms

    /// CowlSubObjPropAxiom - Object subproperty.
    COWL_AT_SUB_OBJ_PROP,

    /// CowlSubObjPropChainAxiom - Object subproperty chain.
    COWL_AT_SUB_OBJ_PROP_CHAIN,

    /// CowlInvObjPropAxiom - Inverse object properties.
    COWL_AT_INV_OBJ_PROP,

    /// CowlNAryObjPropAxiom - Equivalent object properties.
    COWL_AT_EQUIV_OBJ_PROP,

    /// CowlNAryObjPropAxiom - Disjoint object properties.
    COWL_AT_DISJ_OBJ_PROP,

    /// CowlObjPropCharAxiom - Functional object property.
    COWL_AT_FUNC_OBJ_PROP,

    /// CowlObjPropCharAxiom - Inverse functional object property.
    COWL_AT_INV_FUNC_OBJ_PROP,

    /// CowlObjPropCharAxiom - Symmetric object property.
    COWL_AT_SYMM_OBJ_PROP,

    /// CowlObjPropCharAxiom - Asymmetric object property.
    COWL_AT_ASYMM_OBJ_PROP,

    /// CowlObjPropCharAxiom - Transitive object property.
    COWL_AT_TRANS_OBJ_PROP,

    /// CowlObjPropCharAxiom - Reflexive object property.
    COWL_AT_REFL_OBJ_PROP,

    /// CowlObjPropCharAxiom - Irreflexive object property.
    COWL_AT_IRREFL_OBJ_PROP,

    /// CowlObjPropCharAxiom - Object property domain.
    COWL_AT_OBJ_PROP_DOMAIN,

    /// CowlObjPropCharAxiom - Object property range.
    COWL_AT_OBJ_PROP_RANGE,

/// @name Data property axioms

    /// CowlSubDataPropAxiom - Data subproperty.
    COWL_AT_SUB_DATA_PROP,

    /// CowlNAryDataPropAxiom - Equivalent data properties.
    COWL_AT_EQUIV_DATA_PROP,

    /// CowlNAryDataPropAxiom - Disjoint data properties.
    COWL_AT_DISJ_DATA_PROP,

    /// CowlFuncDataPropAxiom - Functional data property.
    COWL_AT_FUNC_DATA_PROP,

    /// CowlDataPropDomainAxiom - Data property domain.
    COWL_AT_DATA_PROP_DOMAIN,

    /// CowlDataPropRangeAxiom - Data property range.
    COWL_AT_DATA_PROP_RANGE,

/// @name Keys

    /// CowlHasKeyAxiom - Has key.
    COWL_AT_HAS_KEY,

/// @name Annotation axioms

    /// CowlAnnotAssertAxiom - Annotation assertion.
    COWL_AT_ANNOT_ASSERT,

    /// CowlSubAnnotPropAxiom - Annotation subproperty.
    COWL_AT_SUB_ANNOT_PROP,

    /// CowlAnnotPropDomainAxiom - Annotation property domain.
    COWL_AT_ANNOT_PROP_DOMAIN,

    /// CowlAnnotPropRangeAxiom - Annotation property range.
    COWL_AT_ANNOT_PROP_RANGE,

/// @name Markers

    /// Number of enum values.
    COWL_AT_COUNT,

    /// First enum value.
    COWL_AT_FIRST = 0

} CowlAxiomType;

COWL_END_DECLS

#endif // COWL_AXIOM_TYPE_H
