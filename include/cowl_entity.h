/**
 * Declares CowlEntity and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
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
/// @endcond

/**
 * Represents an [Entity] in the OWL 2 specification.
 *
 * [Entity]: https://www.w3.org/TR/owl2-syntax/#Entities.2C_Literals.2C_and_Anonymous_Individuals
 *
 * @superstruct{CowlPrimitive}
 * @struct CowlEntity
 */
cowl_struct_decl(CowlEntity);

/**
 * @defgroup CowlEntity CowlEntity API
 * @{
 */

/**
 * Gets the type of the entity.
 *
 * @param entity The entity.
 * @return The type.
 */
COWL_API
COWL_PURE
CowlEntityType cowl_entity_get_type(CowlAnyEntity *entity);

/**
 * Gets the IRI of the entity.
 *
 * @param entity The entity.
 * @return The IRI.
 */
COWL_API
COWL_PURE
CowlIRI *cowl_entity_get_iri(CowlAnyEntity *entity);

/**
 * Checks whether the entity is reserved, i.e. if its IRI is in the reserved vocabulary.
 *
 * @param entity The entity.
 * @return True if the entity is reserved, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_entity_is_reserved(CowlAnyEntity *entity);

#if COWL_ENTITY_IDS

/**
 * Gets the increasing unique identifier associated to the specified entity.
 *
 * @param entity The entity.
 * @return Unique identifier.
 *
 * @note Only available if `COWL_ENTITY_IDS` is defined. Enabling this API ensures entities are
 *       tracked and given a numeric identifier for the lifetime of the executable,
 *       which can be a useful property to have in some applications. Bear in mind that this
 *       also means entities are never deallocated, which can affect memory usage.
 */
COWL_API
COWL_PURE
ulib_uint cowl_entity_get_id(CowlAnyEntity *entity);

/**
 * Returns the entity that has the specified identifier.
 *
 * @param id Unique identifier.
 * @return Entity with the specified identifier, or NULL if no entity has the specified identifier.
 *
 * @note Only available if `COWL_ENTITY_IDS` is defined.
 * @see @func{#cowl_entity_get_id()}
 */
COWL_API
COWL_PURE
CowlAnyEntity *cowl_entity_with_id(ulib_uint id);

#endif

/// @}

COWL_END_DECLS

#endif // COWL_ENTITY_H
