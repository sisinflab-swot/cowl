/**
 * Declares CowlObjProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_H
#define COWL_OBJ_PROP_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/**
 * Represents an [ObjectProperty] in the OWL 2 specification.
 *
 * [ObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Object_Properties
 *
 * @superstruct{CowlObjPropExp,CowlEntity}
 * @struct CowlObjProp
 */
cowl_struct_decl(CowlObjProp);

/**
 * @defgroup CowlObjProp CowlObjProp API
 * @{
 */

/**
 * Returns an object property.
 *
 * @param iri IRI of the object property.
 * @return Object property, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjProp *cowl_obj_prop(CowlIRI *iri) {
    return (CowlObjProp *)cowl_entity_get_impl(COWL_OT_OPE_OBJ_PROP, iri);
}

/**
 * Returns an object property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Object property, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjProp *cowl_obj_prop_from_string(UString string) {
    return (CowlObjProp *)cowl_entity_from_string_impl(COWL_OT_OPE_OBJ_PROP, string);
}

/**
 * Returns a object property given the string literal representing its IRI.
 *
 * @param str @type{char const []} String literal.
 * @return @type{#CowlObjProp *} Object property, or NULL on error.
 */
COWL_RETAINED
#define cowl_obj_prop_from_static(str) cowl_obj_prop_from_string(ustring_literal(str))

/**
 * Gets the IRI of the specified object property.
 *
 * @param prop The object property.
 * @return The IRI.
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_H
