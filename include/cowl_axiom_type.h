/**
 * Defines the CowlAxiomType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_TYPE_H
#define COWL_AXIOM_TYPE_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Represents the type of @type{#CowlAxiom}.
typedef enum CowlAxiomType {

    /// @name Declaration/definition

    /// @type{#CowlDeclAxiom} - Declaration.
    COWL_AT_DECL,

    /// @type{#CowlDatatypeDefAxiom} - Datatype definition.
    COWL_AT_DATATYPE_DEF,

    /// @name Class axioms

    /// @type{#CowlSubClsAxiom} - Subclass.
    COWL_AT_SUB_CLASS,

    /// @type{#CowlNAryClsAxiom} - Equivalent classes.
    COWL_AT_EQUIV_CLASSES,

    /// @type{#CowlNAryClsAxiom} - Disjoint classes.
    COWL_AT_DISJ_CLASSES,

    /// @type{#CowlDisjUnionAxiom} - Disjoint union.
    COWL_AT_DISJ_UNION,

    /// @name Individual axioms

    /// @type{#CowlClsAssertAxiom} - Class assertion.
    COWL_AT_CLASS_ASSERT,

    /// @type{#CowlNAryIndAxiom} - Same individual.
    COWL_AT_SAME_IND,

    /// @type{#CowlNAryIndAxiom} - Different individuals.
    COWL_AT_DIFF_IND,

    /// @type{#CowlObjPropAssertAxiom} - Object property assertion.
    COWL_AT_OBJ_PROP_ASSERT,

    /// @type{#CowlObjPropAssertAxiom} - Negative object property assertion.
    COWL_AT_NEG_OBJ_PROP_ASSERT,

    /// @type{#CowlDataPropAssertAxiom} - Data property assertion.
    COWL_AT_DATA_PROP_ASSERT,

    /// @type{#CowlDataPropAssertAxiom} - Negative data property assertion.
    COWL_AT_NEG_DATA_PROP_ASSERT,

    /// @name Object property axioms

    /// @type{#CowlSubObjPropAxiom} - Object subproperty.
    COWL_AT_SUB_OBJ_PROP,

    /// @type{#CowlInvObjPropAxiom} - Inverse object properties.
    COWL_AT_INV_OBJ_PROP,

    /// @type{#CowlNAryObjPropAxiom} - Equivalent object properties.
    COWL_AT_EQUIV_OBJ_PROP,

    /// @type{#CowlNAryObjPropAxiom} - Disjoint object properties.
    COWL_AT_DISJ_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Functional object property.
    COWL_AT_FUNC_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Inverse functional object property.
    COWL_AT_INV_FUNC_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Symmetric object property.
    COWL_AT_SYMM_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Asymmetric object property.
    COWL_AT_ASYMM_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Transitive object property.
    COWL_AT_TRANS_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Reflexive object property.
    COWL_AT_REFL_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Irreflexive object property.
    COWL_AT_IRREFL_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Object property domain.
    COWL_AT_OBJ_PROP_DOMAIN,

    /// @type{#CowlObjPropCharAxiom} - Object property range.
    COWL_AT_OBJ_PROP_RANGE,

    /// @name Data property axioms

    /// @type{#CowlSubDataPropAxiom} - Data subproperty.
    COWL_AT_SUB_DATA_PROP,

    /// @type{#CowlNAryDataPropAxiom} - Equivalent data properties.
    COWL_AT_EQUIV_DATA_PROP,

    /// @type{#CowlNAryDataPropAxiom} - Disjoint data properties.
    COWL_AT_DISJ_DATA_PROP,

    /// @type{#CowlFuncDataPropAxiom} - Functional data property.
    COWL_AT_FUNC_DATA_PROP,

    /// @type{#CowlDataPropDomainAxiom} - Data property domain.
    COWL_AT_DATA_PROP_DOMAIN,

    /// @type{#CowlDataPropRangeAxiom} - Data property range.
    COWL_AT_DATA_PROP_RANGE,

    /// @name Keys

    /// @type{#CowlHasKeyAxiom} - Has key.
    COWL_AT_HAS_KEY,

    /// @name Annotation axioms

    /// @type{#CowlAnnotAssertAxiom} - Annotation assertion.
    COWL_AT_ANNOT_ASSERT,

    /// @type{#CowlSubAnnotPropAxiom} - Annotation subproperty.
    COWL_AT_SUB_ANNOT_PROP,

    /// @type{#CowlAnnotPropDomainAxiom} - Annotation property domain.
    COWL_AT_ANNOT_PROP_DOMAIN,

    /// @type{#CowlAnnotPropRangeAxiom} - Annotation property range.
    COWL_AT_ANNOT_PROP_RANGE,

    /// @name Markers

    /// Number of enum values.
    COWL_AT_COUNT,

    /// First enum value.
    COWL_AT_FIRST = 0

} CowlAxiomType;

COWL_END_DECLS

#endif // COWL_AXIOM_TYPE_H
