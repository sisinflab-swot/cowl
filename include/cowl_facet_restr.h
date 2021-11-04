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

#include "cowl_facet.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
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
COWL_PUBLIC
CowlFacetRestr* cowl_facet_restr_get(CowlFacet facet, CowlLiteral *value);

/**
 * Retains the specified facet restriction.
 *
 * @param restr The facet restriction.
 * @return Retained facet restriction.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
CowlFacetRestr* cowl_facet_restr_retain(CowlFacetRestr *restr);

/**
 * Releases the specified facet restriction.
 *
 * @param restr The facet restriction.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
void cowl_facet_restr_release(CowlFacetRestr *restr);

/**
 * Gets the facet.
 *
 * @param restr The facet restriction.
 * @return The facet.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
CowlFacet cowl_facet_restr_get_facet(CowlFacetRestr *restr);

/**
 * Gets the restriction value.
 *
 * @param restr The facet restriction.
 * @return The restriction value.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
CowlLiteral* cowl_facet_restr_get_value(CowlFacetRestr *restr);

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
COWL_PUBLIC
CowlString* cowl_facet_restr_to_string(CowlFacetRestr *restr);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
bool cowl_facet_restr_equals(CowlFacetRestr *lhs, CowlFacetRestr *rhs);

/**
 * Hash function.
 *
 * @param restr The facet restriction.
 * @return The hash value.
 *
 * @public @memberof CowlFacetRestr
 */
COWL_PUBLIC
ulib_uint cowl_facet_restr_hash(CowlFacetRestr *restr);

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
COWL_PUBLIC
bool cowl_facet_restr_iterate_primitives(CowlFacetRestr *restr, CowlPrimitiveFlags flags,
                                         CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_H
