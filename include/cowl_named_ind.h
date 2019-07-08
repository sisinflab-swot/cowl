/**
 * Declares CowlNamedInd and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NAMED_IND_H
#define COWL_NAMED_IND_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlNamedInd);
/// @endcond

/**
 * Represents a [NamedIndividual] in the OWL 2 specification.
 *
 * [NamedIndividual]: https://www.w3.org/TR/owl2-syntax/#Named_Individuals
 *
 * @struct CowlNamedInd
 * @extends CowlIndividual
 */

/**
 * Returns a retained named individual.
 *
 * @param iri IRI of the individual.
 * @return Retained named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
CowlNamedInd* cowl_named_ind_get(CowlIRI *iri);

/**
 * Retains the specified named individual.
 *
 * @param ind The named individual.
 * @return Retained named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind);

/**
 * Releases the specified named individual.
 *
 * @param ind The named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
void cowl_named_ind_release(CowlNamedInd *ind);

/**
 * Gets the IRI of the named individual.
 *
 * @param ind The named individual.
 * @return IRI of the named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs);

/**
 * Hash function.
 *
 * @param ind The named individual.
 * @return The hash value.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
cowl_uint_t cowl_named_ind_hash(CowlNamedInd *ind);

/**
 * Iterates over the signature of the specified named individual.
 *
 * @param ind The named individual.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNamedInd
 */
COWL_PUBLIC
bool cowl_named_ind_iterate_signature(CowlNamedInd *ind, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_NAMED_IND_H
