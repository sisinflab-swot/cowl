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
/// @endcond

/**
 * Represents an [AnonymousIndividual] in the OWL 2 specification.
 *
 * [AnonymousIndividual]: https://www.w3.org/TR/owl2-syntax/#Anonymous_Individuals
 *
 * @superstruct{CowlIndividual,CowlPrimitive,CowlAnnotValue}
 * @struct CowlAnonInd
 */
cowl_struct_decl(CowlAnonInd);

/**
 * @defgroup CowlAnonInd CowlAnonInd API
 * @{
 */

/**
 * Returns an anonymous individual.
 *
 * @param id Anonymous individual identifier.
 * @return Anonymous individual, or NULL on error.
 *
 * @note By passing NULL as the identifier, a new identifier is randomly generated.
 */
COWL_API
COWL_RETAINED
CowlAnonInd *cowl_anon_ind(CowlString *id);

/**
 * Returns an anonymous individual given the string representation of its identifier.
 *
 * @param string Anonymous individual identifier.
 * @return Anonymous individual, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlAnonInd *cowl_anon_ind_from_string(UString string);

/**
 * Returns an anonymous individual given a string literal representing its identifier.
 *
 * @param str @type{char const []} String literal.
 * @return @type{#CowlAnonInd *} Anonymous individual, or NULL on error.
 */
COWL_RETAINED
#define cowl_anon_ind_from_static(str) cowl_anon_ind_from_string(ustring_literal(str))

/**
 * Gets the node ID of the specified anonymous individual.
 *
 * @param ind The anonymous individual.
 * @return Node ID.
 */
COWL_API
COWL_PURE
CowlString *cowl_anon_ind_get_id(CowlAnonInd *ind);

/// @}

COWL_END_DECLS

#endif // COWL_ANON_IND_H
