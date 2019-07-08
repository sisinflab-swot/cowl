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
 * @return Retained class.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
CowlClass* cowl_class_get(CowlIRI *iri);

/**
 * Retains the specified class.
 *
 * @param cls The class.
 * @return Retained Class.
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
cowl_uint_t cowl_class_hash(CowlClass *cls);

/**
 * Iterates over the signature of the specified class.
 *
 * @param cls The class.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlClass
 */
COWL_PUBLIC
bool cowl_class_iterate_signature(CowlClass *cls, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_CLASS_H
