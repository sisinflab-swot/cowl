/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_TYPE_H
#define COWL_AXIOM_TYPE_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// Represents the type of axioms which can belong to ontologies.
typedef enum CowlAxiomType {

#pragma mark - Declaration/definition

    /// Represents declaration axioms.
        CAT_DECLARATION,

    /// Represents datatype definition axioms.
        CAT_DATATYPE_DEFINITION,

#pragma mark - Class axioms

    /// Represents equivalent classes axioms.
        CAT_EQUIVALENT_CLASSES,

    /// Represents subclass axioms.
        CAT_SUBCLASS,

    /// Represents disjoint classes axioms.
        CAT_DISJOINT_CLASSES,

    /// Represents disjoint union axioms.
        CAT_DISJOINT_UNION,

#pragma mark - Individual axioms

    /// Represents class assertion axioms.
        CAT_CLASS_ASSERTION,

    /// Represents same individual axioms.
        CAT_SAME_INDIVIDUAL,

    /// Represents different individuals axioms.
        CAT_DIFFERENT_INDIVIDUALS,

    /// Represents object property assertion axioms.
        CAT_OBJ_PROP_ASSERTION,

    /// Represents negative object property assertion axioms.
        CAT_NEGATIVE_OBJ_PROP_ASSERTION,

    /// Represents data property assertion axioms.
        CAT_DATA_PROP_ASSERTION,

    /// Represents negative data property assertion axioms.
        CAT_NEGATIVE_DATA_PROP_ASSERTION,

#pragma mark - Object property axioms

    /// Represents equivalent object properties axioms.
        CAT_EQUIVALENT_OBJ_PROP,

    /// Represents sub-object property axioms.
        CAT_SUB_OBJ_PROP,

    /// Represents inverse object properties axioms.
        CAT_INVERSE_OBJ_PROP,

    /// Represents functional object property axioms.
        CAT_FUNCTIONAL_OBJ_PROP,

    /// Represents inverse functional object property axioms.
        CAT_INVERSE_FUNCTIONAL_OBJ_PROP,

    /// Represents symmetric object property axioms.
        CAT_SYMMETRIC_OBJ_PROP,

    /// Represents asymmetric object property axioms.
        CAT_ASYMMETRIC_OBJ_PROP,

    /// Represents transitive object property axioms.
        CAT_TRANSITIVE_OBJ_PROP,

    /// Represents reflexive object property axioms.
        CAT_REFLEXIVE_OBJ_PROP,

    /// Represents irreflexive object property axioms.
        CAT_IRREFLEXIVE_OBJ_PROP,

    /// Represents object property domain axioms.
        CAT_OBJ_PROP_DOMAIN,

    /// Represents object property range axioms.
        CAT_OBJ_PROP_RANGE,

    /// Represents disjoint object properties axioms.
        CAT_DISJOINT_OBJ_PROP,

    /// Represents sub-property chain axioms.
        CAT_SUB_PROP_CHAIN,

#pragma mark - Data property axioms

    /// Represents equivalent data properties axioms.
        CAT_EQUIVALENT_DATA_PROP,

    /// Represents sub-data property axioms.
        CAT_SUB_DATA_PROP,

    /// Represents functional data property axioms.
        CAT_FUNCTIONAL_DATA_PROP,

    /// Represents data property domain axioms.
        CAT_DATA_PROP_DOMAIN,

    /// Represents data property range axioms.
        CAT_DATA_PROP_RANGE,

    /// Represents disjoint data properties axioms.
        CAT_DISJOINT_DATA_PROP,

#pragma mark - Keys

    /// Represents has key axioms.
        CAT_HAS_KEY,

#pragma mark - Annotation axioms

    /// Represents annotation assertion axioms.
        CAT_ANNOT_ASSERTION,

    /// Represents sub-annotation property axioms.
        CAT_SUB_ANNOT_PROP,

    /// Represents annotation property domain axioms.
        CAT_ANNOT_PROP_DOMAIN,

    /// Represents annotation property range axioms.
        CAT_ANNOT_PROP_RANGE

} CowlAxiomType;

COWL_END_DECLS

#endif // COWL_AXIOM_TYPE_H
