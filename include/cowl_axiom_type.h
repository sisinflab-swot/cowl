/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_TYPE_H
#define COWL_AXIOM_TYPE_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// Represents the type of axioms which can belong to ontologies.
typedef enum CowlAxiomType {

/// @name Declaration/definition

    /// Represents declaration axioms.
        COWL_AT_DECL,

    /// Represents datatype definition axioms.
        COWL_AT_DATATYPE_DEF,

/// @name Class axioms

    /// Represents subclass axioms.
        COWL_AT_SUB_CLASS,

    /// Represents equivalent classes axioms.
        COWL_AT_EQUIV_CLASSES,

    /// Represents disjoint classes axioms.
        COWL_AT_DISJ_CLASSES,

    /// Represents disjoint union axioms.
        COWL_AT_DISJ_UNION,

/// @name Individual axioms

    /// Represents class assertion axioms.
        COWL_AT_CLASS_ASSERT,

    /// Represents same individual axioms.
        COWL_AT_SAME_IND,

    /// Represents different individuals axioms.
        COWL_AT_DIFF_IND,

    /// Represents object property assertion axioms.
        COWL_AT_OBJ_PROP_ASSERT,

    /// Represents negative object property assertion axioms.
        COWL_AT_NEG_OBJ_PROP_ASSERT,

    /// Represents data property assertion axioms.
        COWL_AT_DATA_PROP_ASSERT,

    /// Represents negative data property assertion axioms.
        COWL_AT_NEG_DATA_PROP_ASSERT,

/// @name Object property axioms

    /// Represents sub-object property axioms.
        COWL_AT_SUB_OBJ_PROP,

    /// Represents sub-property chain axioms.
        COWL_AT_SUB_OBJ_PROP_CHAIN,

    /// Represents inverse object properties axioms.
        COWL_AT_INV_OBJ_PROP,

    /// Represents equivalent object properties axioms.
        COWL_AT_EQUIV_OBJ_PROP,

    /// Represents disjoint object properties axioms.
        COWL_AT_DISJ_OBJ_PROP,

    /// Represents functional object property axioms.
        COWL_AT_FUNC_OBJ_PROP,

    /// Represents inverse functional object property axioms.
        COWL_AT_INV_FUNC_OBJ_PROP,

    /// Represents symmetric object property axioms.
        COWL_AT_SYMM_OBJ_PROP,

    /// Represents asymmetric object property axioms.
        COWL_AT_ASYMM_OBJ_PROP,

    /// Represents transitive object property axioms.
        COWL_AT_TRANS_OBJ_PROP,

    /// Represents reflexive object property axioms.
        COWL_AT_REFL_OBJ_PROP,

    /// Represents irreflexive object property axioms.
        COWL_AT_IRREFL_OBJ_PROP,

    /// Represents object property domain axioms.
        COWL_AT_OBJ_PROP_DOMAIN,

    /// Represents object property range axioms.
        COWL_AT_OBJ_PROP_RANGE,

/// @name Data property axioms

    /// Represents sub-data property axioms.
        COWL_AT_SUB_DATA_PROP,

    /// Represents equivalent data properties axioms.
        COWL_AT_EQUIV_DATA_PROP,

    /// Represents disjoint data properties axioms.
        COWL_AT_DISJ_DATA_PROP,

    /// Represents functional data property axioms.
        COWL_AT_FUNC_DATA_PROP,

    /// Represents data property domain axioms.
        COWL_AT_DATA_PROP_DOMAIN,

    /// Represents data property range axioms.
        COWL_AT_DATA_PROP_RANGE,

/// @name Keys

    /// Represents has key axioms.
        COWL_AT_HAS_KEY,

/// @name Annotation axioms

    /// Represents annotation assertion axioms.
        COWL_AT_ANNOT_ASSERT,

    /// Represents sub-annotation property axioms.
        COWL_AT_SUB_ANNOT_PROP,

    /// Represents annotation property domain axioms.
        COWL_AT_ANNOT_PROP_DOMAIN,

    /// Represents annotation property range axioms.
        COWL_AT_ANNOT_PROP_RANGE,

/// @name Markers

    /// Number of axiom types.
        COWL_AT_COUNT,

    /// First axiom type.
        COWL_AT_FIRST = 0

} CowlAxiomType;

#define cowl_axiom_type_equals(lhs, rhs) ((lhs) == (rhs))
#define cowl_axiom_type_hash(axiom_type) (cowl_uint_t)(axiom_type)

COWL_END_DECLS

#endif // COWL_AXIOM_TYPE_H
