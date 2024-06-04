/**
 * Defines CowlAxiomFlags and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_FLAGS_H
#define COWL_AXIOM_FLAGS_H

#include "cowl_axiom_type.h"

COWL_BEGIN_DECLS

/// Size of the @type{#CowlAxiomFlags} type in bits.
#define COWL_AF 64

/**
 * @defgroup CowlAxiomFlags_type CowlAxiomFlags type and values
 * @{
 */

/**
 * Flags to control iteration over axioms.
 *
 * @alias typedef UBit(N) CowlAxiomFlags;
 */
typedef UBit(COWL_AF) CowlAxiomFlags;

/// Iterate over no axioms.
#define COWL_AF_NONE ubit_none(COWL_AF)

/// Iterate over all axioms.
#define COWL_AF_ALL ubit(COWL_AF, ubit_bit(COWL_AF, COWL_AT_COUNT) - 1)

// Declaration/definition

/// Iterate over declaration axioms (@type{#CowlDeclAxiom}).
#define COWL_AF_DECL ubit_bit(COWL_AF, COWL_AT_DECL)

/// Iterate over datatype definition axioms (@type{#CowlDatatypeDefAxiom}).
#define COWL_AF_DATATYPE_DEF ubit_bit(COWL_AF, COWL_AT_DATATYPE_DEF)

// Class axioms

/// Iterate over subclass axioms (@type{#CowlSubClsAxiom}).
#define COWL_AF_SUB_CLASS ubit_bit(COWL_AF, COWL_AT_SUB_CLASS)

/// Iterate over equivalent classes axioms (@type{#CowlNAryClsAxiom}).
#define COWL_AF_EQUIV_CLASSES ubit_bit(COWL_AF, COWL_AT_EQUIV_CLASSES)

/// Iterate over disjoint classes axioms (@type{#CowlNAryClsAxiom}).
#define COWL_AF_DISJ_CLASSES ubit_bit(COWL_AF, COWL_AT_DISJ_CLASSES)

/// Iterate over disjoint union axioms (@type{#CowlDisjUnionAxiom}).
#define COWL_AF_DISJ_UNION ubit_bit(COWL_AF, COWL_AT_DISJ_UNION)

// Individual axioms

/// Iterate over class assertion axioms (@type{#CowlClsAssertAxiom}).
#define COWL_AF_CLASS_ASSERT ubit_bit(COWL_AF, COWL_AT_CLASS_ASSERT)

/// Iterate over same individual axioms (@type{#CowlNAryIndAxiom}).
#define COWL_AF_SAME_IND ubit_bit(COWL_AF, COWL_AT_SAME_IND)

/// Iterate over different individuals axioms (@type{#CowlNAryIndAxiom}).
#define COWL_AF_DIFF_IND ubit_bit(COWL_AF, COWL_AT_DIFF_IND)

/// Iterate over object property assertion axioms (@type{#CowlObjPropAssertAxiom}).
#define COWL_AF_OBJ_PROP_ASSERT ubit_bit(COWL_AF, COWL_AT_OBJ_PROP_ASSERT)

/// Iterate over negative object property assertion axioms (@type{#CowlObjPropAssertAxiom}).
#define COWL_AF_NEG_OBJ_PROP_ASSERT ubit_bit(COWL_AF, COWL_AT_NEG_OBJ_PROP_ASSERT)

/// Iterate over data property assertion axioms (@type{#CowlDataPropAssertAxiom}).
#define COWL_AF_DATA_PROP_ASSERT ubit_bit(COWL_AF, COWL_AT_DATA_PROP_ASSERT)

/// Iterate over negative data property assertion axioms (@type{#CowlDataPropAssertAxiom}).
#define COWL_AF_NEG_DATA_PROP_ASSERT ubit_bit(COWL_AF, COWL_AT_NEG_DATA_PROP_ASSERT)

// Object property axioms

/// Iterate over object subproperty axioms (@type{#CowlSubObjPropAxiom}).
#define COWL_AF_SUB_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_SUB_OBJ_PROP)

/// Iterate over inverse object properties axioms (@type{#CowlInvObjPropAxiom}).
#define COWL_AF_INV_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_INV_OBJ_PROP)

/// Iterate over equivalent object properties axioms (@type{#CowlNAryObjPropAxiom}).
#define COWL_AF_EQUIV_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_EQUIV_OBJ_PROP)

/// Iterate over disjoint object properties axioms (@type{#CowlNAryObjPropAxiom}).
#define COWL_AF_DISJ_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_DISJ_OBJ_PROP)

/// Iterate over functional object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_FUNC_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_FUNC_OBJ_PROP)

/// Iterate over inverse functional object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_INV_FUNC_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_INV_FUNC_OBJ_PROP)

/// Iterate over symmetric object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_SYMM_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_SYMM_OBJ_PROP)

/// Iterate over asymmetric object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_ASYMM_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_ASYMM_OBJ_PROP)

/// Iterate over transitive object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_TRANS_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_TRANS_OBJ_PROP)

/// Iterate over reflexive object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_REFL_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_REFL_OBJ_PROP)

/// Iterate over irreflexive object property axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_IRREFL_OBJ_PROP ubit_bit(COWL_AF, COWL_AT_IRREFL_OBJ_PROP)

/// Iterate over object property domain axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_OBJ_PROP_DOMAIN ubit_bit(COWL_AF, COWL_AT_OBJ_PROP_DOMAIN)

/// Iterate over object property range axioms (@type{#CowlObjPropCharAxiom}).
#define COWL_AF_OBJ_PROP_RANGE ubit_bit(COWL_AF, COWL_AT_OBJ_PROP_RANGE)

// Data property axioms

/// Iterate over data subproperty axioms (@type{#CowlSubDataPropAxiom}).
#define COWL_AF_SUB_DATA_PROP ubit_bit(COWL_AF, COWL_AT_SUB_DATA_PROP)

/// Iterate over equivalent data properties axioms (@type{#CowlNAryDataPropAxiom}).
#define COWL_AF_EQUIV_DATA_PROP ubit_bit(COWL_AF, COWL_AT_EQUIV_DATA_PROP)

/// Iterate over disjoint data properties axioms (@type{#CowlNAryDataPropAxiom}).
#define COWL_AF_DISJ_DATA_PROP ubit_bit(COWL_AF, COWL_AT_DISJ_DATA_PROP)

/// Iterate over functional data property axioms (@type{#CowlFuncDataPropAxiom}).
#define COWL_AF_FUNC_DATA_PROP ubit_bit(COWL_AF, COWL_AT_FUNC_DATA_PROP)

/// Iterate over data property domain axioms (@type{#CowlDataPropDomainAxiom}).
#define COWL_AF_DATA_PROP_DOMAIN ubit_bit(COWL_AF, COWL_AT_DATA_PROP_DOMAIN)

/// Iterate over data property range axioms (@type{#CowlDataPropRangeAxiom}).
#define COWL_AF_DATA_PROP_RANGE ubit_bit(COWL_AF, COWL_AT_DATA_PROP_RANGE)

// Keys

/// Iterate over has key axioms (@type{#CowlHasKeyAxiom}).
#define COWL_AF_HAS_KEY ubit_bit(COWL_AF, COWL_AT_HAS_KEY)

// Annotation axioms

/// Iterate over annotation assertion axioms (@type{#CowlAnnotAssertAxiom}).
#define COWL_AF_ANNOT_ASSERT ubit_bit(COWL_AF, COWL_AT_ANNOT_ASSERT)

/// Iterate over annotation subproperty axioms (@type{#CowlSubAnnotPropAxiom}).
#define COWL_AF_SUB_ANNOT_PROP ubit_bit(COWL_AF, COWL_AT_SUB_ANNOT_PROP)

/// Iterate over annotation property domain axioms (@type{#CowlAnnotPropDomainAxiom}).
#define COWL_AF_ANNOT_PROP_DOMAIN ubit_bit(COWL_AF, COWL_AT_ANNOT_PROP_DOMAIN)

/// Iterate over annotation property range axioms (@type{#CowlAnnotPropRangeAxiom}).
#define COWL_AF_ANNOT_PROP_RANGE ubit_bit(COWL_AF, COWL_AT_ANNOT_PROP_RANGE)

/// @}

/**
 * @defgroup CowlAxiomFlags_api CowlAxiomFlags API
 * @{
 */

/**
 * Returns a bitmask with a bit set for the specified axiom type.
 *
 * @param type Axiom type.
 * @return Flags.
 */
COWL_CONST
COWL_INLINE
CowlAxiomFlags cowl_axiom_flags_from_type(CowlAxiomType type) {
    return ubit_bit(COWL_AF, type);
}

/**
 * Checks whether the specified type is included in the flags.
 *
 * @param flags Axiom flags.
 * @param type Axiom type.
 * @return True if the type is included in the flags, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_axiom_flags_has_type(CowlAxiomFlags flags, CowlAxiomType type) {
    return ubit_is_set(COWL_AF, flags, ubit_bit(COWL_AF, type));
}

/**
 * Checks whether the flags match all axiom types.
 *
 * @param flags Axiom flags.
 * @return True if the flags match all axiom types, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_axiom_flags_has_all_types(CowlAxiomFlags flags) {
    return ubit_is_set(COWL_AF, flags, COWL_AF_ALL);
}

/**
 * Checks whether the flags match no axiom types.
 *
 * @param flags Axiom flags.
 * @return True if the flags match no axiom types, false otherwise.
 */
COWL_CONST
COWL_INLINE
bool cowl_axiom_flags_has_no_types(CowlAxiomFlags flags) {
    return !ubit_is_any_set(COWL_AF, flags, COWL_AF_ALL);
}

/**
 * Iterates over the flags, executing the specified code block for each axiom type.
 *
 * @param flags Axiom flags.
 * @param type Name of the variable holding the axiom type.
 */
#define cowl_axiom_flags_foreach_type(flags, type)                                                 \
    /** NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange) */                               \
    for (CowlAxiomType type = ubit_first_set(COWL_AF, flags); type < COWL_AT_COUNT;                \
         (type = ubit_first_set(COWL_AF,                                                           \
                                ubit_unset(COWL_AF, flags, ubit_bit(COWL_AF, type + 1) - 1))))     \
    /** NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange) */

/// @}

COWL_END_DECLS

#endif // COWL_AXIOM_FLAGS_H
