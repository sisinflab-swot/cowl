/**
 * Declares CowlDeclAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DECL_AXIOM_H
#define COWL_DECL_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlEntity);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [Declaration] in the OWL 2 specification.
 *
 * [Declaration]: https://www.w3.org/TR/owl2-syntax/#Entity_Declarations_and_Typing
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDeclAxiom
 */
cowl_struct_decl(CowlDeclAxiom);

/**
 * @defgroup CowlDeclAxiom CowlDeclAxiom API
 * @{
 */

/**
 * Returns a declaration axiom.
 *
 * @param entity The declared entity.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDeclAxiom *cowl_decl_axiom(CowlAnyEntity *entity, CowlVector *annot) {
    return (CowlDeclAxiom *)cowl_get_impl_1_annot(COWL_OT_A_DECL, entity, annot);
}

/**
 * Gets the declared entity.
 *
 * @param axiom The axiom.
 * @return The entity.
 */
COWL_PURE
COWL_INLINE
CowlEntity *cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom) {
    return (CowlEntity *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H
