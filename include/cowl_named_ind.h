/**
 * Declares CowlNamedInd and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NAMED_IND_H
#define COWL_NAMED_IND_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
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
 * @return Retained named individual, or NULL on error.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    return (CowlNamedInd *)cowl_entity_get_impl(COWL_OT_I_NAMED, iri);
}

/**
 * Returns a retained named individual given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained named individual, or NULL on error.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
CowlNamedInd* cowl_named_ind_from_string(UString string) {
    return (CowlNamedInd *)cowl_entity_from_string_impl(COWL_OT_I_NAMED, string);
}

/**
 * Returns a retained named individual given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlNamedInd *] Retained named individual, or NULL on error.
 *
 * @public @related CowlNamedInd
 */
#define cowl_named_ind_from_static(CSTR) cowl_named_ind_from_string(ustring_literal(CSTR))

/**
 * Retains the specified named individual.
 *
 * @param ind The named individual.
 * @return Retained named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind) {
    return (CowlNamedInd *)cowl_retain(ind);
}

/**
 * Releases the specified named individual.
 *
 * @param ind The named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
void cowl_named_ind_release(CowlNamedInd *ind) {
    cowl_entity_release((CowlEntity *)ind);
}

/**
 * Gets the IRI of the named individual.
 *
 * @param ind The named individual.
 * @return IRI of the named individual.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return cowl_entity_get_iri((CowlEntity *)ind);
}

/**
 * Returns the string representation of the specified named individual.
 *
 * @param ind The named individual.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
CowlString* cowl_named_ind_to_string(CowlNamedInd *ind) {
    return cowl_entity_to_string((CowlEntity *)ind);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param ind The named individual.
 * @return The hash value.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
ulib_uint cowl_named_ind_hash(CowlNamedInd *ind) {
    return uhash_ptr_hash(ind);
}

/**
 * Iterates over this named individual.
 *
 * @param ind The named individual.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNamedInd
 */
COWL_INLINE
bool cowl_named_ind_iterate_primitives(CowlNamedInd *ind, CowlPrimitiveFlags flags,
                                       CowlIterator *iter) {
    return cowl_entity_iterate_primitives((CowlEntity *)ind, flags, iter);
}

COWL_END_DECLS

#endif // COWL_NAMED_IND_H
