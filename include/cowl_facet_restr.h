/**
 * Declares CowlFacetRestr and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
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
 * @extends CowlObject
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
CowlFacetRestr *cowl_facet_restr(CowlIRI *facet, CowlLiteral *value) {
    return (CowlFacetRestr *)cowl_get_impl_2(COWL_OT_FACET_RESTR, facet, value);
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
CowlIRI *cowl_facet_restr_get_facet(CowlFacetRestr *restr) {
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
CowlLiteral *cowl_facet_restr_get_value(CowlFacetRestr *restr) {
    return (CowlLiteral *)cowl_get_field(restr, 1);
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

COWL_END_DECLS

#endif // COWL_FACET_RESTR_H
