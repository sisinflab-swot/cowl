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

/// @cond
cowl_struct_decl(CowlObjProp);
/// @endcond

/**
 * Represents an [ObjectProperty] in the OWL 2 specification.
 *
 * [ObjectProperty]: https://www.w3.org/TR/owl2-syntax/#Object_Properties
 *
 * @struct CowlObjProp
 * @extends CowlObjPropExp
 * @extends CowlEntity
 */

/**
 * Returns a retained object property.
 *
 * @param iri IRI of the object property.
 * @return Retained object property, or NULL on error.
 *
 * @public @memberof CowlObjProp
 */
COWL_INLINE
CowlObjProp *cowl_obj_prop(CowlIRI *iri) {
    return (CowlObjProp *)cowl_entity_get_impl(COWL_OT_OPE_OBJ_PROP, iri);
}

/**
 * Returns a retained object property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained object property, or NULL on error.
 *
 * @public @memberof CowlObjProp
 */
COWL_INLINE
CowlObjProp *cowl_obj_prop_from_string(UString string) {
    return (CowlObjProp *)cowl_entity_from_string_impl(COWL_OT_OPE_OBJ_PROP, string);
}

/**
 * Returns a retained object property given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlObjProp *] Retained object property, or NULL on error.
 *
 * @public @related CowlObjProp
 */
#define cowl_obj_prop_from_static(CSTR) cowl_obj_prop_from_string(ustring_literal(CSTR))

/**
 * Gets the IRI of the specified object property.
 *
 * @param prop The object property.
 * @return The IRI.
 *
 * @public @memberof CowlObjProp
 */
COWL_INLINE
CowlIRI *cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjProp
 */
COWL_INLINE
bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param prop The property.
 * @return The hash value.
 *
 * @public @memberof CowlObjProp
 */
COWL_INLINE
ulib_uint cowl_obj_prop_hash(CowlObjProp *prop) {
    return uhash_ptr_hash(prop);
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_H
