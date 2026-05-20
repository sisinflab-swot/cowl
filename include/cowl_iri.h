/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include "cowl_attrs.h"
#include "cowl_string.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/**
 * Represents [International Resource Identifiers].
 *
 * [International Resource Identifiers]: https://www.w3.org/TR/owl2-syntax/#IRIs
 *
 * @superstruct{CowlAnnotValue}
 * @struct CowlIRI
 */
cowl_struct_decl(CowlIRI);

/**
 * @defgroup CowlIRI CowlIRI API
 * @{
 */

/**
 * Returns an IRI whose string representation is the concatenation of the specified strings.
 *
 * @param prefix The prefix.
 * @param suffix The suffix.
 * @return IRI, or NULL on error
 */
COWL_API
COWL_RETAINED
CowlIRI *cowl_iri(CowlString *prefix, CowlString *suffix);

/**
 * Returns an IRI given its string representation.
 *
 * @param string String representation of the IRI.
 * @return IRI, or NULL on error
 */
COWL_API
COWL_RETAINED
CowlIRI *cowl_iri_from_string(UString string);

/**
 * Returns an IRI given its literal string representation.
 *
 * @param str String literal.
 * @return IRI, or NULL on error
 *
 * @alias COWL_RETAINED CowlIRI *cowl_iri_from_literal(char const str[]);
 */
#define cowl_iri_from_literal(str) (cowl_iri_from_string(ustring_literal(str)))

/**
 * @copydoc cowl_iri_from_literal
 * @deprecated Use @func{cowl_iri_from_literal} instead.
 * @alias CowlIRI *cowl_iri_from_static(char const str[]);
 */
#define cowl_iri_from_static(str) COWL_DEPRECATED_MACRO cowl_iri_from_literal(str)

/**
 * Gets the namespace of the specified IRI.
 *
 * @param iri The IRI.
 * @return The namespace.
 */
COWL_API
COWL_PURE
CowlString *cowl_iri_get_ns(CowlIRI *iri);

/**
 * Gets the remainder of the specified IRI.
 *
 * @param iri The IRI.
 * @return The remainder.
 */
COWL_API
COWL_PURE
CowlString *cowl_iri_get_rem(CowlIRI *iri);

/**
 * Checks whether the IRI has a remainder.
 *
 * @param iri The IRI.
 * @return True if the IRI has a remainder, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_iri_has_rem(CowlIRI *iri) {
    return cowl_string_get_length(cowl_iri_get_rem(iri)) > 0;
}

/**
 * Checks whether the IRI is in the reserved vocabulary.
 *
 * @param iri The IRI.
 * @return True if the IRI is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_iri_is_reserved(CowlIRI *iri);

/**
 * Returns the string representation of the specified IRI.
 *
 * @param iri The IRI.
 * @return String representation, or @val{ustring_null} on error.
 *
 * @destructor{ustring_deinit}
 * @note The IRI is represented as the concatenation of the namespace and the remainder,
 *       without any additional markup (e.g. angle brackets).
 */
COWL_API
UString cowl_iri_to_string(CowlIRI *iri);

/// @}

COWL_END_DECLS

#endif // COWL_IRI_H
