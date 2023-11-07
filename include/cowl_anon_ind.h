/**
 * Declares CowlAnonInd and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANON_IND_H
#define COWL_ANON_IND_H

#include "cowl_primitive.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlAnonInd);
/// @endcond

/**
 * Represents an [AnonymousIndividual] in the OWL 2 specification.
 *
 * [AnonymousIndividual]: https://www.w3.org/TR/owl2-syntax/#Anonymous_Individuals
 *
 * @struct CowlAnonInd
 * @extends CowlIndividual
 * @extends CowlPrimitive
 * @extends CowlAnnotValue
 */

/**
 * Returns an anonymous individual.
 *
 * @param id Anonymous individual identifier.
 * @return Anonymous individual, or NULL on error.
 *
 * @note By passing NULL as the identifier, a new identifier is randomly generated.
 *
 * @public @memberof CowlAnonInd
 */
COWL_API
COWL_RETAINED
CowlAnonInd *cowl_anon_ind(CowlString *id);

/**
 * Returns an anonymous individual given the string representation of its identifier.
 *
 * @param string Anonymous individual identifier.
 * @return Anonymous individual, or NULL on error.
 *
 * @public @memberof CowlAnonInd
 */
COWL_API
COWL_RETAINED
CowlAnonInd *cowl_anon_ind_from_string(UString string);

/**
 * Returns an anonymous individual given the static string representation of its identifier.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlAnonInd *] Anonymous individual, or NULL on error.
 *
 * @public @related CowlAnonInd
 */
COWL_RETAINED
#define cowl_anon_ind_from_static(CSTR) cowl_anon_ind_from_string(ustring_literal(CSTR))

/**
 * Gets the node ID of the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return Node ID.
 *
 * @public @memberof CowlAnonInd
 */
COWL_API
COWL_PURE
CowlString *cowl_anon_ind_get_id(CowlAnonInd *ind);

COWL_END_DECLS

#endif // COWL_ANON_IND_H
