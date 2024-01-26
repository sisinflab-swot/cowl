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
/// @endcond

/**
 * Represents a facet restriction used to restrict a particular @type{#CowlDatatype}.
 *
 * @see https://www.w3.org/TR/owl2-syntax/#Datatype_Maps
 *
 * @superstruct{CowlObject}
 * @struct CowlFacetRestr
 */
cowl_struct_decl(CowlFacetRestr);

/**
 * @defgroup CowlFacetRestr CowlFacetRestr API
 * @{
 */

/**
 * Returns a facet restriction.
 *
 * @param facet The facet.
 * @param value The restriction value.
 * @return Facet restriction, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlFacetRestr *cowl_facet_restr(CowlIRI *facet, CowlLiteral *value) {
    return (CowlFacetRestr *)cowl_get_impl_2(COWL_OT_FACET_RESTR, facet, value);
}

/**
 * Gets the facet.
 *
 * @param restr The facet restriction.
 * @return The facet.
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_facet_restr_get_facet(CowlFacetRestr *restr) {
    return (CowlIRI *)cowl_get_field(restr, 0);
}

/**
 * Gets the restriction value.
 *
 * @param restr The facet restriction.
 * @return The restriction value.
 */
COWL_PURE
COWL_INLINE
CowlLiteral *cowl_facet_restr_get_value(CowlFacetRestr *restr) {
    return (CowlLiteral *)cowl_get_field(restr, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_FACET_RESTR_H
