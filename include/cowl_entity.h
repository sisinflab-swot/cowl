/**
 * Declares CowlEntity and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ENTITY_H
#define COWL_ENTITY_H

#include "cowl_entity_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlEntity);
/// @endcond

/**
 * Represents an [Entity] in the OWL 2 specification.
 *
 * [Entity]: https://www.w3.org/TR/owl2-syntax/#Entities.2C_Literals.2C_and_Anonymous_Individuals
 *
 * @struct CowlEntity
 * @extends CowlPrimitive
 */

/**
 * Retains the entity.
 *
 * @param entity The entity.
 * @return Retained entity.
 *
 * @public @memberof CowlEntity
 */
COWL_INLINE
CowlAnyEntity* cowl_entity_retain(CowlAnyEntity *entity) {
    return cowl_retain(entity);
}

/**
 * Releases the entity.
 *
 * @param entity The entity.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
void cowl_entity_release(CowlAnyEntity *entity);

/**
 * Gets the type of the entity.
 *
 * @param entity The entity.
 * @return The type.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
CowlEntityType cowl_entity_get_type(CowlAnyEntity *entity);

/**
 * Gets the IRI of the entity.
 *
 * @param entity The entity.
 * @return The IRI.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
CowlIRI* cowl_entity_get_iri(CowlAnyEntity *entity);

/**
 * Returns the string representation of the specified entity.
 *
 * @param entity The entity.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
CowlString* cowl_entity_to_string(CowlAnyEntity *entity);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlEntity
 */
COWL_INLINE
bool cowl_entity_equals(CowlAnyEntity *lhs, CowlAnyEntity *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param entity The entity.
 * @return The hash value.
 *
 * @public @memberof CowlEntity
 */
COWL_INLINE
ulib_uint cowl_entity_hash(CowlAnyEntity *entity) {
    return uhash_ptr_hash(entity);
}

/**
 * Iterates over this entity.
 *
 * @param entity The entity.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlEntity
 */
COWL_INLINE
bool cowl_entity_iterate_primitives(CowlAnyEntity *entity, CowlPrimitiveFlags flags,
                                    CowlIterator *iter) {
    return cowl_iterate_primitives(entity, flags, iter);
}

COWL_END_DECLS

#endif // COWL_ENTITY_H
