/**
 * Defines CowlAxiomIndex and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_INDEX_H
#define COWL_AXIOM_INDEX_H

#include "cowl_axiom_flags.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

/// @cond
uvec_decl(CowlObjectPtr);
/// @endcond

/// Axiom index parameters.
typedef struct CowlAxiomIndex {

    /// Match axioms of the specified types.
    CowlAxiomFlags types;

    /// Match axioms referencing all the specified primitives.
    UVec(CowlObjectPtr) primitives;

} CowlAxiomIndex;

/**
 * @defgroup CowlAxiomIndex CowlAxiomIndex API
 * @{
 */

/**
 * Returns a new axiom index.
 *
 * @return Axiom index.
 */
COWL_CONST
COWL_INLINE
CowlAxiomIndex cowl_axiom_index(void) {
    CowlAxiomIndex ret = { COWL_AF_ALL, uvec(CowlObjectPtr) };
    return ret;
}

/**
 * De-initializes an axiom index previously initialized via @func{#cowl_axiom_index()}.
 *
 * @param index Axiom index.
 */
COWL_INLINE
void cowl_axiom_index_deinit(CowlAxiomIndex *index) {
    uvec_deinit(CowlObjectPtr, &index->primitives);
}

/**
 * Adds the specified axiom type to the index.
 *
 * @param index Axiom index.
 * @param type Axiom type.
 */
COWL_INLINE
void cowl_axiom_index_add_type(CowlAxiomIndex *index, CowlAxiomType type) {
    index->types = ubit_set(COWL_AF, index->types, cowl_axiom_flags_from_type(type));
}

/**
 * Removes the specified axiom type from the index.
 *
 * @param index Axiom index.
 * @param type Axiom type.
 */
COWL_INLINE
void cowl_axiom_index_remove_type(CowlAxiomIndex *index, CowlAxiomType type) {
    index->types = ubit_unset(COWL_AF, index->types, cowl_axiom_flags_from_type(type));
}

/**
 * Adds the specified primitive to the index.
 *
 * @param index Axiom index.
 * @param primitive Primitive.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_axiom_index_add_primitive(CowlAxiomIndex *index, CowlAnyPrimitive *primitive) {
    uvec_ret ret = uvec_push_unique(CowlObjectPtr, &index->primitives, primitive);
    return ret == UVEC_ERR ? COWL_ERR_MEM : COWL_OK;
}

/**
 * Removes the specified primitive from the index.
 *
 * @param index Axiom index.
 * @param primitive Primitive.
 */
COWL_INLINE
void cowl_axiom_index_remove_primitive(CowlAxiomIndex *index, CowlAnyPrimitive *primitive) {
    uvec_remove(CowlObjectPtr, &index->primitives, primitive);
}

/// @}

COWL_END_DECLS

#endif // COWL_AXIOM_INDEX_H
