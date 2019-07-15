/**
 * Declares CowlOntologyID and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_ID_H
#define COWL_ONTOLOGY_ID_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntologyID);
/// @endcond

/**
 * An object that identifies an ontology.
 *
 * @struct CowlOntologyID
 * @see [Ontology IRI and version IRI]
 *
 * [Ontology IRI and version IRI]: https://www.w3.org/TR/owl2-syntax/#Ontology_IRI_and_Version_IRI
 */

/**
 * Gets the ontology IRI.
 *
 * @param id The ontology ID.
 * @return The ontology IRI.
 *
 * @note Can be NULL.
 *
 * @public @memberof CowlOntologyID
 */
COWL_PUBLIC
CowlIRI* cowl_ontology_id_get_onto_iri(CowlOntologyID *id);

/**
 * Gets the version IRI.
 *
 * @param id The ontology ID.
 * @return The version IRI.
 *
 * @note Can be NULL.
 *
 * @public @memberof CowlOntologyID
 */
COWL_PUBLIC
CowlIRI* cowl_ontology_id_get_version_iri(CowlOntologyID *id);


/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @note Ontology IDs are considered equal if they have the same ontology IRI and version IRI.
 *       Since OWL 2 allows for both the ontology and version IRIs to be simultaneously empty,
 *       in that case the ontology IDs are considered different unless they are the same instance.
 *
 * @public @memberof CowlOntologyID
 */
COWL_PUBLIC
bool cowl_ontology_id_equals(CowlOntologyID *lhs, CowlOntologyID *rhs);

/**
 * Hash function.
 *
 * @param id The ontology ID.
 * @return The hash value.
 *
 * @public @memberof CowlOntologyID
 */
COWL_PUBLIC
cowl_uint_t cowl_ontology_id_hash(CowlOntologyID *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_H
