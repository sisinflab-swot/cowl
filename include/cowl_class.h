/**
 * Declares CowlClass and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLASS_H
#define COWL_CLASS_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlClass);
/// @endcond

/**
 * Represents a [Class] in the OWL 2 specification.
 *
 * [Class]: https://www.w3.org/TR/owl2-syntax/#Classes
 *
 * @struct CowlClass
 * @extends CowlClsExp
 */

/**
 * Returns a retained class.
 *
 * @param iri IRI of the class.
 * @return Retained class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
CowlClass* cowl_class_get(CowlIRI *iri);

/**
 * Returns a retained class given the string representation of its IRI.
 *
 * @param cstring String representation of the IRI.
 * @param length Length of the string.
 * @return Retained class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
CowlClass* cowl_class_from_cstring(char const *cstring, size_t length);

/**
 * Returns a retained class given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlClass *] Retained class, or NULL on error.
 *
 * @public @related CowlClass
 */
#define cowl_class_from_static(CSTR) (cowl_class_from_cstring((CSTR), sizeof(CSTR) - 1))

/**
 * Retains the specified class.
 *
 * @param cls The class.
 * @return Retained class.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
CowlClass* cowl_class_retain(CowlClass *cls);

/**
 * Releases the specified class.
 *
 * @param cls The class.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
void cowl_class_release(CowlClass *cls);

/**
 * Gets the IRI of the specified class.
 *
 * @param cls The class.
 * @return IRI of the class.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
CowlIRI* cowl_class_get_iri(CowlClass *cls);

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
COWL_PUBLIC
CowlString* cowl_class_to_string(CowlClass *cls);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs);

/**
 * Hash function.
 *
 * @param cls The class.
 * @return The hash value.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
cowl_uint cowl_class_hash(CowlClass *cls);

/**
 * Iterates over this class.
 *
 * @param cls The class.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
bool cowl_class_iterate_primitives(CowlClass *cls, CowlIterator *iter, CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_CLASS_H
