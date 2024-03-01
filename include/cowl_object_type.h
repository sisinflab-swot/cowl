/**
 * Defines the CowlObjectType enumeration.
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

#include "cowl_attrs.h"
#include "cowl_macros.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
/// @endcond

/// Represents the type of @type{#CowlObject}.
typedef enum CowlObjectType {

    /// @name Base types

    /// @type{#CowlString} - String.
    COWL_OT_STRING = 0,

    /// @type{#CowlVector} - Vector.
    COWL_OT_VECTOR,

    /// @type{#CowlTable} - Hash table.
    COWL_OT_TABLE,

    /// @type{#CowlIRI} - IRI.
    COWL_OT_IRI,

    /// @type{#CowlLiteral} - Literal.
    COWL_OT_LITERAL,

    /// @type{#CowlFacetRestr} - Facet restriction.
    COWL_OT_FACET_RESTR,

    /// @type{#CowlOntology} - Ontology.
    COWL_OT_ONTOLOGY,

    /// @type{#CowlManager} - Ontology manager.
    COWL_OT_MANAGER,

    /// @type{#CowlSymTable} - Symbol table.
    COWL_OT_SYM_TABLE,

    /// @type{#CowlIStream} - Ontology input stream.
    COWL_OT_ISTREAM,

    /// @type{#CowlOStream} - Ontology output stream.
    COWL_OT_OSTREAM,

    /// @type{#CowlAnnotation} - Annotation.
    COWL_OT_ANNOTATION,

    /// @type{#CowlAnnotProp} - Annotation property.
    COWL_OT_ANNOT_PROP,

    /// @name Axioms

    /// @type{#CowlDeclAxiom} - Declaration.
    COWL_OT_A_DECL,

    /// @type{#CowlDatatypeDefAxiom} - Datatype definition.
    COWL_OT_A_DATATYPE_DEF,

    /// @type{#CowlSubClsAxiom} - Subclass.
    COWL_OT_A_SUB_CLASS,

    /// @type{#CowlNAryClsAxiom} - Equivalent classes.
    COWL_OT_A_EQUIV_CLASSES,

    /// @type{#CowlNAryClsAxiom} - Disjoint classes.
    COWL_OT_A_DISJ_CLASSES,

    /// @type{#CowlDisjUnionAxiom} - Disjoint union.
    COWL_OT_A_DISJ_UNION,

    /// @type{#CowlClsAssertAxiom} - Class assertion.
    COWL_OT_A_CLASS_ASSERT,

    /// @type{#CowlNAryIndAxiom} - Same individual.
    COWL_OT_A_SAME_IND,

    /// @type{#CowlNAryIndAxiom} - Different individuals.
    COWL_OT_A_DIFF_IND,

    /// @type{#CowlObjPropAssertAxiom} - Object property assertion.
    COWL_OT_A_OBJ_PROP_ASSERT,

    /// @type{#CowlObjPropAssertAxiom} - Negative object property assertion.
    COWL_OT_A_NEG_OBJ_PROP_ASSERT,

    /// @type{#CowlDataPropAssertAxiom} - Data property assertion.
    COWL_OT_A_DATA_PROP_ASSERT,

    /// @type{#CowlDataPropAssertAxiom} - Negative data property assertion.
    COWL_OT_A_NEG_DATA_PROP_ASSERT,

    /// @type{#CowlSubObjPropAxiom} - Object subproperty.
    COWL_OT_A_SUB_OBJ_PROP,

    /// @type{#CowlInvObjPropAxiom} - Inverse object properties.
    COWL_OT_A_INV_OBJ_PROP,

    /// @type{#CowlNAryObjPropAxiom} - Equivalent object properties.
    COWL_OT_A_EQUIV_OBJ_PROP,

    /// @type{#CowlNAryObjPropAxiom} - Disjoint object properties.
    COWL_OT_A_DISJ_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Functional object property.
    COWL_OT_A_FUNC_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Inverse functional object property.
    COWL_OT_A_INV_FUNC_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Symmetric object property.
    COWL_OT_A_SYMM_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Asymmetric object property.
    COWL_OT_A_ASYMM_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Transitive object property.
    COWL_OT_A_TRANS_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Reflexive object property.
    COWL_OT_A_REFL_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Irreflexive object property.
    COWL_OT_A_IRREFL_OBJ_PROP,

    /// @type{#CowlObjPropCharAxiom} - Object property domain.
    COWL_OT_A_OBJ_PROP_DOMAIN,

    /// @type{#CowlObjPropCharAxiom} - Object property range.
    COWL_OT_A_OBJ_PROP_RANGE,

    /// @type{#CowlSubDataPropAxiom} - Data subproperty.
    COWL_OT_A_SUB_DATA_PROP,

    /// @type{#CowlNAryDataPropAxiom} - Equivalent data properties.
    COWL_OT_A_EQUIV_DATA_PROP,

    /// @type{#CowlNAryDataPropAxiom} - Disjoint data properties.
    COWL_OT_A_DISJ_DATA_PROP,

    /// @type{#CowlFuncDataPropAxiom} - Functional data property.
    COWL_OT_A_FUNC_DATA_PROP,

    /// @type{#CowlDataPropDomainAxiom} - Data property domain.
    COWL_OT_A_DATA_PROP_DOMAIN,

    /// @type{#CowlDataPropRangeAxiom} - Data property range.
    COWL_OT_A_DATA_PROP_RANGE,

    /// @type{#CowlHasKeyAxiom} - Has key.
    COWL_OT_A_HAS_KEY,

    /// @type{#CowlAnnotAssertAxiom} - Annotation assertion.
    COWL_OT_A_ANNOT_ASSERT,

    /// @type{#CowlSubAnnotPropAxiom} - Annotation subproperty.
    COWL_OT_A_SUB_ANNOT_PROP,

    /// @type{#CowlAnnotPropDomainAxiom} - Annotation property domain.
    COWL_OT_A_ANNOT_PROP_DOMAIN,

    /// @type{#CowlAnnotPropRangeAxiom} - Annotation property range.
    COWL_OT_A_ANNOT_PROP_RANGE,

    /// @name Class expressions

    /// @type{#CowlClass} - class.
    COWL_OT_CE_CLASS,

    /// @type{#CowlObjQuant} - "some values from" object property restriction.
    COWL_OT_CE_OBJ_SOME,

    /// @type{#CowlObjQuant} - "all values from" object property restriction.
    COWL_OT_CE_OBJ_ALL,

    /// @type{#CowlObjCard} - "minimum cardinality" object property restriction.
    COWL_OT_CE_OBJ_MIN_CARD,

    /// @type{#CowlObjCard} - "maximum cardinality" object property restriction.
    COWL_OT_CE_OBJ_MAX_CARD,

    /// @type{#CowlObjCard} - "exact cardinality" object property restriction.
    COWL_OT_CE_OBJ_EXACT_CARD,

    /// @type{#CowlObjHasValue} - "has value" object property restriction.
    COWL_OT_CE_OBJ_HAS_VALUE,

    /// @type{#CowlObjHasSelf} - "has self" object property restriction.
    COWL_OT_CE_OBJ_HAS_SELF,

    /// @type{#CowlDataQuant} - "some values from" data property restriction.
    COWL_OT_CE_DATA_SOME,

    /// @type{#CowlDataQuant} - "all values from" data property restriction.
    COWL_OT_CE_DATA_ALL,

    /// @type{#CowlDataCard} - "min cardinality" data property restriction.
    COWL_OT_CE_DATA_MIN_CARD,

    /// @type{#CowlDataCard} - "max cardinality" data property restriction.
    COWL_OT_CE_DATA_MAX_CARD,

    /// @type{#CowlDataCard} - "exact cardinality" data property restriction.
    COWL_OT_CE_DATA_EXACT_CARD,

    /// @type{#CowlDataHasValue} - "has value" data property restriction.
    COWL_OT_CE_DATA_HAS_VALUE,

    /// @type{#CowlNAryBool} - Intersection of class expressions.
    COWL_OT_CE_OBJ_INTERSECT,

    /// @type{#CowlNAryBool} - Union of class expressions.
    COWL_OT_CE_OBJ_UNION,

    /// @type{#CowlObjCompl} - Complement of a class expression.
    COWL_OT_CE_OBJ_COMPL,

    /// @type{#CowlObjOneOf} - Enumeration of individuals.
    COWL_OT_CE_OBJ_ONE_OF,

    /// @name Data property expressions

    /// @type{#CowlDataProp} - Data property.
    COWL_OT_DPE_DATA_PROP,

    /// @name Data ranges

    /// @type{#CowlDatatype} - Datatype.
    COWL_OT_DR_DATATYPE,

    /// @type{#CowlDatatypeRestr} - Datatype restriction.
    COWL_OT_DR_DATATYPE_RESTR,

    /// @type{#CowlNAryData} - Intersection of data ranges.
    COWL_OT_DR_DATA_INTERSECT,

    /// @type{#CowlNAryData} - Union of data ranges.
    COWL_OT_DR_DATA_UNION,

    /// @type{#CowlDataCompl} - Complement of data ranges.
    COWL_OT_DR_DATA_COMPL,

    /// @type{#CowlDataOneOf} - Enumeration of literals.
    COWL_OT_DR_DATA_ONE_OF,

    /// @name Individuals

    /// @type{#CowlAnonInd} - Anonymous individual.
    COWL_OT_I_ANONYMOUS,

    /// @type{#CowlNamedInd} - Named individual.
    COWL_OT_I_NAMED,

    /// @name Object property expressions

    /// @type{#CowlObjProp} - Object property.
    COWL_OT_OPE_OBJ_PROP,

    /// @type{#CowlInvObjProp} - Inverse object property.
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

/**
 * @defgroup CowlObjectType CowlObjectType API
 * @{
 */

/**
 * Returns a human-readable string representation of the specified object type.
 *
 * @param type Object type.
 * @return String representation, or NULL on error.
 *
 * @note You must not modify or free the returned string.
 */
COWL_API
COWL_CONST
UString cowl_object_type_to_ustring(CowlObjectType type);

/**
 * Returns a human-readable string representation of the specified object type.
 *
 * @param type Object type.
 * @return String representation, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlString *cowl_object_type_to_string(CowlObjectType type);

/**
 * Returns the object type given its string representation.
 *
 * @param string String representation.
 * @return Object type, or an invalid object type (>=@val{#COWL_OT_COUNT}) on error.
 */
COWL_API
COWL_PURE
CowlObjectType cowl_object_type_from_string(UString string);

/// @}

COWL_END_DECLS

#endif // COWL_OBJECT_TYPE_H
