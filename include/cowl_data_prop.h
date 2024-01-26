/**
 * Declares CowlDataProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_H
#define COWL_DATA_PROP_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/**
 * Represents a [DataProperty] in the OWL 2 specification.
 *
 * [DataProperty]: https://www.w3.org/TR/owl2-syntax/#Data_Properties
 *
 * @superstruct{CowlDataPropExp,CowlEntity}
 * @struct CowlDataProp
 */
cowl_struct_decl(CowlDataProp);

/**
 * @defgroup CowlDataProp CowlDataProp API
 * @{
 */

/**
 * Returns a data property.
 *
 * @param iri IRI of the data property.
 * @return Data property, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataProp *cowl_data_prop(CowlIRI *iri) {
    return (CowlDataProp *)cowl_entity_get_impl(COWL_OT_DPE_DATA_PROP, iri);
}

/**
 * Returns a data property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Data property, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataProp *cowl_data_prop_from_string(UString string) {
    return (CowlDataProp *)cowl_entity_from_string_impl(COWL_OT_DPE_DATA_PROP, string);
}

/**
 * Returns a data property given the string literal representing its IRI.
 *
 * @param str @type{char const[]} String literal.
 * @return @type{#CowlDataProp *} Data property, or NULL on error.
 */
COWL_RETAINED
#define cowl_data_prop_from_static(str) cowl_data_prop_from_string(ustring_literal(str))

/**
 * Gets the IRI of the specified data property.
 *
 * @param prop The data property.
 * @return The IRI.
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_data_prop_get_iri(CowlDataProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_PROP_H
