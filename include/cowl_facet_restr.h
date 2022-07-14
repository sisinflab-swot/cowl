/**
 * Declares CowlFacetRestr and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_RESTR_H
#define COWL_FACET_RESTR_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlFacetRestr);
/// @endcond

/**
 * Represents a facet restriction used to restrict a particular CowlDatatype.
 *
 * @see https://www.w3.org/TR/owl2-syntax/#Datatype_Maps
 *
 * @struct CowlFacetRestr
 */

/**
 * Returns a retained facet restriction.
 *
 * @param facet The facet.
 * @param value The restriction value.
 * @return Retained facet restriction, or NULL on error.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
CowlFacetRestr* cowl_facet_restr_get(CowlIRI *facet, CowlLiteral *value) {
    return (CowlFacetRestr *)cowl_get_impl_2(COWL_OT_FACET_RESTR, facet, value);
}

/**
 * Retains the specified facet restriction.
 *
 * @param restr The facet restriction.
 * @return Retained facet restriction.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
CowlFacetRestr* cowl_facet_restr_retain(CowlFacetRestr *restr) {
    return (CowlFacetRestr *)cowl_retain(restr);
}

/**
 * Releases the specified facet restriction.
 *
 * @param restr The facet restriction.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
void cowl_facet_restr_release(CowlFacetRestr *restr) {
    cowl_release_impl(restr);
}

/**
 * Gets the facet.
 *
 * @param restr The facet restriction.
 * @return The facet.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
CowlIRI* cowl_facet_restr_get_facet(CowlFacetRestr *restr) {
    return (CowlIRI *)cowl_get_field(restr, 0);
}

/**
 * Gets the restriction value.
 *
 * @param restr The facet restriction.
 * @return The restriction value.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
CowlLiteral* cowl_facet_restr_get_value(CowlFacetRestr *restr) {
    return (CowlLiteral *)cowl_get_field(restr, 1);
}

/**
 * Returns the string representation of the specified facet restriction.
 *
 * @param restr The facet restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
CowlString* cowl_facet_restr_to_string(CowlFacetRestr *restr) {
    return cowl_to_string(restr);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
bool cowl_facet_restr_equals(CowlFacetRestr *lhs, CowlFacetRestr *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param restr The facet restriction.
 * @return The hash value.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
ulib_uint cowl_facet_restr_hash(CowlFacetRestr *restr) {
    return cowl_hash_impl(restr);
}

/**
 * Iterates over the primitives referenced by specified facet restriction.
 *
 * @param restr The facet restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_INLINE
bool cowl_facet_restr_iterate_primitives(CowlFacetRestr *restr, CowlPrimitiveFlags flags,
                                         CowlIterator *iter) {
    return cowl_iterate_primitives_impl(restr, flags, iter);
}

COWL_END_DECLS

#endif // COWL_FACET_RESTR_H
