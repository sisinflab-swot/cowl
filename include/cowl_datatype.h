/**
 * Declares CowlDatatype and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_H
#define COWL_DATATYPE_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
/// @endcond

/**
 * Represents a [Datatype] in the OWL 2 specification.
 *
 * [Datatype]: https://www.w3.org/TR/owl2-syntax/#Datatypes
 *
 * @struct CowlDatatype
 * @extends CowlDataRange
 * @extends CowlEntity
 */

/**
 * Returns a retained datatype.
 *
 * @param iri IRI of the datatype.
 * @return Retained datatype, or NULL on error.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
CowlDatatype* cowl_datatype(CowlIRI *iri) {
    return (CowlDatatype *)cowl_entity_get_impl(COWL_OT_DR_DATATYPE, iri);
}

/**
 * Returns a retained datatype given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained datatype, or NULL on error.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
CowlDatatype* cowl_datatype_from_string(UString string) {
    return (CowlDatatype *)cowl_entity_from_string_impl(COWL_OT_DR_DATATYPE, string);
}

/**
 * Returns a retained datatype given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlDatatype *] Retained datatype, or NULL on error.
 *
 * @public @related CowlDatatype
 */
#define cowl_datatype_from_static(CSTR) cowl_datatype_from_string(ustring_literal(CSTR))

/**
 * Retains the specified datatype.
 *
 * @param dt The datatype.
 * @return Retained datatype.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
CowlDatatype* cowl_datatype_retain(CowlDatatype *dt) {
    return (CowlDatatype *)cowl_retain(dt);
}

/**
 * Releases the specified datatype.
 *
 * @param dt The datatype.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
void cowl_datatype_release(CowlDatatype *dt) {
    cowl_entity_release((CowlEntity *)dt);
}

/**
 * Gets the IRI of the specified datatype.
 *
 * @param dt The datatype.
 * @return The IRI.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
CowlIRI* cowl_datatype_get_iri(CowlDatatype *dt) {
    return cowl_entity_get_iri((CowlEntity *)dt);
}

/**
 * Returns the string representation of the specified datatype.
 *
 * @param dt The datatype.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
CowlString* cowl_datatype_to_string(CowlDatatype *dt) {
    return cowl_entity_to_string((CowlEntity *)dt);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param dt The datatype.
 * @return The hash value.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
ulib_uint cowl_datatype_hash(CowlDatatype *dt) {
    return uhash_ptr_hash(dt);
}

/**
 * Iterates over this datatype.
 *
 * @param dt The datatype.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDatatype
 */
COWL_INLINE
bool cowl_datatype_iterate_primitives(CowlDatatype *dt, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    return cowl_entity_iterate_primitives((CowlEntity *)dt, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATATYPE_H
