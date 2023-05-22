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

/// @cond
cowl_struct_decl(CowlDataProp);
/// @endcond

/**
 * Represents a [DataProperty] in the OWL 2 specification.
 *
 * [DataProperty]: https://www.w3.org/TR/owl2-syntax/#Data_Properties
 *
 * @struct CowlDataProp
 * @extends CowlDataPropExp
 * @extends CowlEntity
 */

/**
 * Returns a retained data property.
 *
 * @param iri IRI of the data property.
 * @return Retained data property, or NULL on error.
 *
 * @public @memberof CowlDataProp
 */
COWL_INLINE
CowlDataProp *cowl_data_prop(CowlIRI *iri) {
    return (CowlDataProp *)cowl_entity_get_impl(COWL_OT_DPE_DATA_PROP, iri);
}

/**
 * Returns a retained data property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained data property, or NULL on error.
 *
 * @public @memberof CowlDataProp
 */
COWL_INLINE
CowlDataProp *cowl_data_prop_from_string(UString string) {
    return (CowlDataProp *)cowl_entity_from_string_impl(COWL_OT_DPE_DATA_PROP, string);
}

/**
 * Returns a retained data property given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlDataProp *] Retained data property, or NULL on error.
 *
 * @public @related CowlDataProp
 */
#define cowl_data_prop_from_static(CSTR) cowl_data_prop_from_string(ustring_literal(CSTR))

/**
 * Gets the IRI of the specified data property.
 *
 * @param prop The data property.
 * @return The IRI.
 *
 * @public @memberof CowlDataProp
 */
COWL_INLINE
CowlIRI *cowl_data_prop_get_iri(CowlDataProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataProp
 */
COWL_INLINE
bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param prop The property.
 * @return The hash value.
 *
 * @public @memberof CowlDataProp
 */
COWL_INLINE
ulib_uint cowl_data_prop_hash(CowlDataProp *prop) {
    return uhash_ptr_hash(prop);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_H
