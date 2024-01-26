/**
 * Declares CowlObjOneOf and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_ONE_OF_H
#define COWL_OBJ_ONE_OF_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents [ObjectOneOf] in the OWL 2 specification.
 *
 * [ObjectOneOf]: https://www.w3.org/TR/owl2-syntax/#Enumeration_of_Individuals
 *
 * @superstruct{CowlClsExp}
 * @struct CowlObjOneOf
 */
cowl_struct_decl(CowlObjOneOf);

/**
 * @defgroup CowlObjOneOf CowlObjOneOf API
 * @{
 */

/**
 * Returns an individual enumeration.
 *
 * @param inds The individuals.
 * @return Individual enumeration, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjOneOf *cowl_obj_one_of(CowlVector *inds) {
    return (CowlObjOneOf *)cowl_get_impl_1(COWL_OT_CE_OBJ_ONE_OF, inds);
}

/**
 * Gets the individuals of the specified enumeration.
 *
 * @param exp The individual enumeration.
 * @return The individuals.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_obj_one_of_get_inds(CowlObjOneOf *exp) {
    return (CowlVector *)cowl_get_field(exp, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_ONE_OF_H
