/**
 * Declares CowlIndividual and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_INDIVIDUAL_H
#define COWL_INDIVIDUAL_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/**
 * Represents an [Individual] in the OWL 2 specification.
 *
 * [Individual]: https://www.w3.org/TR/owl2-syntax/#Individuals
 *
 * @superstruct{CowlPrimitive}
 * @struct CowlIndividual
 */
cowl_struct_decl(CowlIndividual);

/**
 * @defgroup CowlIndividual CowlIndividual API
 * @{
 */

/**
 * Returns true if the underlying individual is named.
 *
 * @param ind The individual.
 * @return True if the underlying individual is named, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_individual_is_named(CowlAnyIndividual *ind) {
    return cowl_get_type(ind) == COWL_OT_I_NAMED;
}

/// @}

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_H
