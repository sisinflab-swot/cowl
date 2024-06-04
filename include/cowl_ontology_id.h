/**
 * Declares CowlOntologyId and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_ID_H
#define COWL_ONTOLOGY_ID_H

#include "cowl_attrs.h"
#include "cowl_macros.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * An object that identifies an ontology.
 *
 * @see [Ontology IRI and version IRI]
 *
 * [Ontology IRI and version IRI]: https://www.w3.org/TR/owl2-syntax/#Ontology_IRI_and_Version_IRI
 */
typedef struct CowlOntologyId {

    /// The ontology IRI.
    CowlIRI *iri;

    /// The version IRI.
    CowlIRI *version;

} CowlOntologyId;

/**
 * @defgroup CowlOntologyId CowlOntologyId API
 * @{
 */

/**
 * Creates the ID of an anonymous ontology.
 *
 * @return ID of an anonymous ontology.
 */
COWL_CONST
COWL_INLINE
CowlOntologyId cowl_ontology_id_anonymous(void) {
    CowlOntologyId id = { NULL, NULL };
    return id;
}

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
 */
COWL_API
COWL_PURE
bool cowl_ontology_id_equals(CowlOntologyId lhs, CowlOntologyId rhs);

/**
 * Hash function.
 *
 * @param id The ontology ID.
 * @return The hash value.
 */
COWL_API
COWL_PURE
ulib_uint cowl_ontology_id_hash(CowlOntologyId id);

/// @}

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_H
