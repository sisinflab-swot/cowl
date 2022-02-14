/**
 * Defines the #CowlObjectType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_TYPE_H
#define COWL_OBJECT_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlObject.
typedef enum CowlObjectType {

/// @name Base types

    /// CowlString - String.
    COWL_OT_STRING = 0,

    /// CowlIRI - IRI.
    COWL_OT_IRI,

    /// CowlLiteral - Literal.
    COWL_OT_LITERAL,

    /// CowlFacetRestr - Facet restriction.
    COWL_OT_FACET_RESTR,

    /// CowlOntology - Ontology.
    COWL_OT_ONTOLOGY,

    /// CowlManager - Ontology manager.
    COWL_OT_MANAGER,

    /// CowlAnnotation - Annotation.
    COWL_OT_ANNOTATION,

    /// CowlAnnotProp - Annotation property.
    COWL_OT_ANNOT_PROP,

/// @name Axioms

    /// CowlDeclAxiom - Declaration.
    COWL_OT_A_DECL,

    /// CowlDatatypeDefAxiom - Datatype definition.
    COWL_OT_A_DATATYPE_DEF,

    /// CowlSubClsAxiom - Subclass.
    COWL_OT_A_SUB_CLASS,

    /// CowlNAryClsAxiom - Equivalent classes.
    COWL_OT_A_EQUIV_CLASSES,

    /// CowlNAryClsAxiom - Disjoint classes.
    COWL_OT_A_DISJ_CLASSES,

    /// CowlDisjUnionAxiom - Disjoint union.
    COWL_OT_A_DISJ_UNION,

    /// CowlClsAssertAxiom - Class assertion.
    COWL_OT_A_CLASS_ASSERT,

    /// CowlNAryIndAxiom - Same individual.
    COWL_OT_A_SAME_IND,

    /// CowlNAryIndAxiom - Different individuals.
    COWL_OT_A_DIFF_IND,

    /// CowlObjPropAssertAxiom - Object property assertion.
    COWL_OT_A_OBJ_PROP_ASSERT,

    /// CowlObjPropAssertAxiom - Negative object property assertion.
    COWL_OT_A_NEG_OBJ_PROP_ASSERT,

    /// CowlDataPropAssertAxiom - Data property assertion.
    COWL_OT_A_DATA_PROP_ASSERT,

    /// CowlDataPropAssertAxiom - Negative data property assertion.
    COWL_OT_A_NEG_DATA_PROP_ASSERT,

    /// CowlSubObjPropAxiom - Object subproperty.
    COWL_OT_A_SUB_OBJ_PROP,

    /// CowlSubObjPropChainAxiom - Object subproperty chain.
    COWL_OT_A_SUB_OBJ_PROP_CHAIN,

    /// CowlInvObjPropAxiom - Inverse object properties.
    COWL_OT_A_INV_OBJ_PROP,

    /// CowlNAryObjPropAxiom - Equivalent object properties.
    COWL_OT_A_EQUIV_OBJ_PROP,

    /// CowlNAryObjPropAxiom - Disjoint object properties.
    COWL_OT_A_DISJ_OBJ_PROP,

    /// CowlObjPropCharAxiom - Functional object property.
    COWL_OT_A_FUNC_OBJ_PROP,

    /// CowlObjPropCharAxiom - Inverse functional object property.
    COWL_OT_A_INV_FUNC_OBJ_PROP,

    /// CowlObjPropCharAxiom - Symmetric object property.
    COWL_OT_A_SYMM_OBJ_PROP,

    /// CowlObjPropCharAxiom - Asymmetric object property.
    COWL_OT_A_ASYMM_OBJ_PROP,

    /// CowlObjPropCharAxiom - Transitive object property.
    COWL_OT_A_TRANS_OBJ_PROP,

    /// CowlObjPropCharAxiom - Reflexive object property.
    COWL_OT_A_REFL_OBJ_PROP,

    /// CowlObjPropCharAxiom - Irreflexive object property.
    COWL_OT_A_IRREFL_OBJ_PROP,

    /// CowlObjPropCharAxiom - Object property domain.
    COWL_OT_A_OBJ_PROP_DOMAIN,

    /// CowlObjPropCharAxiom - Object property range.
    COWL_OT_A_OBJ_PROP_RANGE,

    /// CowlSubDataPropAxiom - Data subproperty.
    COWL_OT_A_SUB_DATA_PROP,

    /// CowlNAryDataPropAxiom - Equivalent data properties.
    COWL_OT_A_EQUIV_DATA_PROP,

    /// CowlNAryDataPropAxiom - Disjoint data properties.
    COWL_OT_A_DISJ_DATA_PROP,

    /// CowlFuncDataPropAxiom - Functional data property.
    COWL_OT_A_FUNC_DATA_PROP,

    /// CowlDataPropDomainAxiom - Data property domain.
    COWL_OT_A_DATA_PROP_DOMAIN,

    /// CowlDataPropRangeAxiom - Data property range.
    COWL_OT_A_DATA_PROP_RANGE,

    /// CowlHasKeyAxiom - Has key.
    COWL_OT_A_HAS_KEY,

    /// CowlAnnotAssertAxiom - Annotation assertion.
    COWL_OT_A_ANNOT_ASSERT,

    /// CowlSubAnnotPropAxiom - Annotation subproperty.
    COWL_OT_A_SUB_ANNOT_PROP,

    /// CowlAnnotPropDomainAxiom - Annotation property domain.
    COWL_OT_A_ANNOT_PROP_DOMAIN,

    /// CowlAnnotPropRangeAxiom - Annotation property range.
    COWL_OT_A_ANNOT_PROP_RANGE,

/// @name Class expressions

    /// CowlClass - class.
    COWL_OT_CE_CLASS,

    /// CowlObjQuant - "some values from" object property restriction.
    COWL_OT_CE_OBJ_SOME,

    /// CowlObjQuant - "all values from" object property restriction.
    COWL_OT_CE_OBJ_ALL,

    /// CowlObjCard - "minimum cardinality" object property restriction.
    COWL_OT_CE_OBJ_MIN_CARD,

    /// CowlObjCard - "maximum cardinality" object property restriction.
    COWL_OT_CE_OBJ_MAX_CARD,

    /// CowlObjCard - "exact cardinality" object property restriction.
    COWL_OT_CE_OBJ_EXACT_CARD,

    /// CowlObjHasValue - "has value" object property restriction.
    COWL_OT_CE_OBJ_HAS_VALUE,

    /// CowlObjHasSelf - "has self" object property restriction.
    COWL_OT_CE_OBJ_HAS_SELF,

    /// CowlDataQuant - "some values from" data property restriction.
    COWL_OT_CE_DATA_SOME,

    /// CowlDataQuant - "all values from" data property restriction.
    COWL_OT_CE_DATA_ALL,

    /// CowlDataCard - "min cardinality" data property restriction.
    COWL_OT_CE_DATA_MIN_CARD,

    /// CowlDataCard - "max cardinality" data property restriction.
    COWL_OT_CE_DATA_MAX_CARD,

    /// CowlDataCard - "exact cardinality" data property restriction.
    COWL_OT_CE_DATA_EXACT_CARD,

    /// CowlDataHasValue - "has value" data property restriction.
    COWL_OT_CE_DATA_HAS_VALUE,

    /// CowlNAryBool - Intersection of class expressions.
    COWL_OT_CE_OBJ_INTERSECT,

    /// CowlNAryBool - Union of class expressions.
    COWL_OT_CE_OBJ_UNION,

    /// CowlObjCompl - Complement of a class expression.
    COWL_OT_CE_OBJ_COMPL,

    /// CowlObjOneOf - Enumeration of individuals.
    COWL_OT_CE_OBJ_ONE_OF,

/// @name Data property expressions

    /// CowlDataProp - Data property.
    COWL_OT_DPE_DATA_PROP,

/// @name Data ranges

    /// CowlDatatype - Datatype.
    COWL_OT_DR_DATATYPE,

    /// CowlDatatypeRestr - Datatype restriction.
    COWL_OT_DR_DATATYPE_RESTR,

    /// CowlNAryData - Intersection of data ranges.
    COWL_OT_DR_DATA_INTERSECT,

    /// CowlNAryData - Union of data ranges.
    COWL_OT_DR_DATA_UNION,

    /// CowlDataCompl - Complement of data ranges.
    COWL_OT_DR_DATA_COMPL,

    /// CowlDataOneOf - Enumeration of literals.
    COWL_OT_DR_DATA_ONE_OF,

/// @name Individuals

    /// CowlAnonInd - Anonymous individual.
    COWL_OT_I_ANONYMOUS,

    /// CowlNamedInd - Named individual.
    COWL_OT_I_NAMED,

/// @name Object property expressions

    /// CowlObjProp - Object property.
    COWL_OT_OPE_OBJ_PROP,

    /// CowlInvObjProp - Inverse object property.
    COWL_OT_OPE_INV_OBJ_PROP,

/// @name Markers

    /// Number of enum values.
    COWL_OT_COUNT,

    /// First enum value.
    COWL_OT_FIRST = 0,

    /// First axiom type.
    COWL_OT_FIRST_A = COWL_OT_A_DECL,

    /// Last axiom type.
    COWL_OT_LAST_A = COWL_OT_A_ANNOT_PROP_RANGE,

    /// First class expression type.
    COWL_OT_FIRST_CE = COWL_OT_CE_CLASS,

    /// Last class expression type.
    COWL_OT_LAST_CE = COWL_OT_CE_OBJ_ONE_OF,

    /// First object property expression type.
    COWL_OT_FIRST_OPE = COWL_OT_OPE_OBJ_PROP,

    /// Last object property expression type.
    COWL_OT_LAST_OPE = COWL_OT_OPE_INV_OBJ_PROP,

    /// First individual type.
    COWL_OT_FIRST_I = COWL_OT_I_ANONYMOUS,

    /// Last individual type.
    COWL_OT_LAST_I = COWL_OT_I_NAMED,

    /// First data range type.
    COWL_OT_FIRST_DR = COWL_OT_DR_DATATYPE,

    /// Last data range type.
    COWL_OT_LAST_DR = COWL_OT_DR_DATA_ONE_OF

} CowlObjectType;

COWL_END_DECLS

#endif // COWL_OBJECT_TYPE_H
