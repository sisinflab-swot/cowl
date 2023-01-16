/**
 * Declares CowlClass and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLASS_H
#define COWL_CLASS_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
/// @endcond

/**
 * Represents a [Class] in the OWL 2 specification.
 *
 * [Class]: https://www.w3.org/TR/owl2-syntax/#Classes
 *
 * @struct CowlClass
 * @extends CowlClsExp
 * @extends CowlEntity
 */

/**
 * Returns a retained class.
 *
 * @param iri IRI of the class.
 * @return Retained class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
CowlClass *cowl_class(CowlIRI *iri) {
    return (CowlClass *)cowl_entity_get_impl(COWL_OT_CE_CLASS, iri);
}

/**
 * Returns a retained class given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
CowlClass *cowl_class_from_string(UString string) {
    return (CowlClass *)cowl_entity_from_string_impl(COWL_OT_CE_CLASS, string);
}

/**
 * Returns a retained class given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlClass *] Retained class, or NULL on error.
 *
 * @public @related CowlClass
 */
#define cowl_class_from_static(CSTR) cowl_class_from_string(ustring_literal(CSTR))

/**
 * Retains the specified class.
 *
 * @param cls The class.
 * @return Retained class.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
CowlClass *cowl_class_retain(CowlClass *cls) {
    return (CowlClass *)cowl_retain(cls);
}

/**
 * Releases the specified class.
 *
 * @param cls The class.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
void cowl_class_release(CowlClass *cls) {
    cowl_entity_release((CowlEntity *)cls);
}

/**
 * Gets the IRI of the specified class.
 *
 * @param cls The class.
 * @return IRI of the class.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
CowlIRI *cowl_class_get_iri(CowlClass *cls) {
    return cowl_entity_get_iri((CowlEntity *)cls);
}

/**
 * Returns the string representation of the specified class.
 *
 * @param cls The class.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
CowlString *cowl_class_to_string(CowlClass *cls) {
    return cowl_entity_to_string((CowlEntity *)cls);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param cls The class.
 * @return The hash value.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
ulib_uint cowl_class_hash(CowlClass *cls) {
    return uhash_ptr_hash(cls);
}

/**
 * Iterates over this class.
 *
 * @param cls The class.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlClass
 */
COWL_INLINE
bool cowl_class_iterate_primitives(CowlClass *cls, CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_entity_iterate_primitives((CowlEntity *)cls, flags, iter);
}

COWL_END_DECLS

#endif // COWL_CLASS_H
