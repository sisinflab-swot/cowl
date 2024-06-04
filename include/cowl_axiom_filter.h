/**
 * Defines CowlAxiomFilter and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_FILTER_H
#define COWL_AXIOM_FILTER_H

#include "cowl_axiom_flags.h"
#include "cowl_ret.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

/// Axiom filter.
typedef struct CowlAxiomFilter {

    /// Match axioms of the specified types.
    CowlAxiomFlags types;

    /// Match axioms referencing all the specified primitives.
    UVec(CowlObjectPtr) primitives;

    /// Match axioms based on the specified closure.
    CowlFilter closure;

} CowlAxiomFilter;

/**
 * @defgroup CowlAxiomFilter CowlAxiomFilter API
 * @{
 */

/**
 * Returns a new axiom filter.
 *
 * @param types Axiom types.
 * @return Axiom filter.
 */
COWL_CONST
COWL_INLINE
CowlAxiomFilter cowl_axiom_filter(CowlAxiomFlags types) {
    CowlAxiomFilter ret = { types, uvec(CowlObjectPtr), ulib_struct_init };
    return ret;
}

/**
 * De-initializes an axiom filter previously initialized via @func{#cowl_axiom_filter()}.
 *
 * @param filter Axiom filter.
 */
COWL_INLINE
void cowl_axiom_filter_deinit(CowlAxiomFilter *filter) {
    uvec_foreach (CowlObjectPtr, &filter->primitives, p) {
        cowl_release(*p.item);
    }
    uvec_deinit(CowlObjectPtr, &filter->primitives);
}

/**
 * Adds the specified axiom type to the filter.
 *
 * @param filter Axiom filter.
 * @param type Axiom type.
 */
COWL_INLINE
void cowl_axiom_filter_add_type(CowlAxiomFilter *filter, CowlAxiomType type) {
    filter->types = ubit_set(COWL_AF, filter->types, cowl_axiom_flags_from_type(type));
}

/**
 * Removes the specified axiom type from the filter.
 *
 * @param filter Axiom filter.
 * @param type Axiom type.
 */
COWL_INLINE
void cowl_axiom_filter_remove_type(CowlAxiomFilter *filter, CowlAxiomType type) {
    filter->types = ubit_unset(COWL_AF, filter->types, cowl_axiom_flags_from_type(type));
}

/**
 * Adds the specified primitive to the filter.
 *
 * @param filter Axiom filter.
 * @param primitive Primitive.
 * @return Return code.
 */
COWL_INLINE
cowl_ret cowl_axiom_filter_add_primitive(CowlAxiomFilter *filter, CowlAnyPrimitive *primitive) {
    uvec_ret ret = uvec_push_unique(CowlObjectPtr, &filter->primitives, primitive);
    if (ret == UVEC_OK) cowl_retain(primitive);
    return ret == UVEC_ERR ? COWL_ERR_MEM : COWL_OK;
}

/**
 * Removes the specified primitive from the filter.
 *
 * @param filter Axiom filter.
 * @param primitive Primitive.
 */
COWL_INLINE
void cowl_axiom_filter_remove_primitive(CowlAxiomFilter *filter, CowlAnyPrimitive *primitive) {
    if (uvec_remove(CowlObjectPtr, &filter->primitives, primitive)) {
        cowl_release(primitive);
    }
    uvec_shrink(CowlObjectPtr, &filter->primitives);
}

/**
 * Sets the filter closure.
 *
 * @param filter Axiom filter.
 * @param closure Filter closure.
 */
COWL_INLINE
void cowl_axiom_filter_set_closure(CowlAxiomFilter *filter, CowlFilter closure) {
    filter->closure = closure;
}

/// @}

COWL_END_DECLS

#endif // COWL_AXIOM_FILTER_H
