/**
 * Defines #CowlFacet enumeration and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FACET_H
#define COWL_FACET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
/// @endcond

/// Represents the facets that can be used for restricting a datatype.
typedef enum CowlFacet {

/// @name Facets

    /// No facet.
        COWL_FACET_NONE = 0,

    /// xsd:length
        COWL_FACET_LENGTH,

    /// xsd:minLength
        COWL_FACET_MIN_LENGTH,

    /// xsd:maxLength
        COWL_FACET_MAX_LENGTH,

    /// xsd:pattern
        COWL_FACET_PATTERN,

    /// xsd:minInclusive
        COWL_FACET_MIN_INCL,

    /// xsd:minExclusive
        COWL_FACET_MIN_EXCL,

    /// xsd:maxInclusive
        COWL_FACET_MAX_INCL,

    /// xsd:maxExclusive
        COWL_FACET_MAX_EXCL,

    /// xsd:totalDigits
        COWL_FACET_TOTAL_DIGITS,

    /// xsd:fractionDigits
        COWL_FACET_FRAC_DIGITS,

    /// xsd:langRange
        COWL_FACET_LANG_RANGE,

/// @name Markers

    /// Number of enum values.
        COWL_FACET_COUNT,

    /// First enum value.
        COWL_FACET_FIRST = 1

} CowlFacet;

/**
 * Returns the facet associated with the specified IRI.
 *
 * @param iri IRI of the facet.
 * @return The facet.
 *
 * @public @related CowlFacetRestr
 */
COWL_PUBLIC
CowlFacet cowl_facet_from_iri(CowlIRI *iri);

/**
 * Returns the IRI of the specified facet.
 *
 * @param facet The facet.
 * @return IRI of the facet.
 *
 * @public @related CowlFacetRestr
 */
COWL_PUBLIC
CowlIRI* cowl_facet_get_iri(CowlFacet facet);

COWL_END_DECLS

#endif // COWL_FACET_H
