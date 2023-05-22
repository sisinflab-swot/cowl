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
cowl_struct_decl(CowlDeclAxiom);
/// @endcond

/**
 * Represents a [Declaration] in the OWL 2 specification.
 *
 * [Declaration]: https://www.w3.org/TR/owl2-syntax/#Entity_Declarations_and_Typing
 *
 * @struct CowlDeclAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained declaration axiom.
 *
 * @param entity The declared entity.
 * @param annot [optional] The annotations.
 * @return Retained declaration.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
CowlDeclAxiom *cowl_decl_axiom(CowlAnyEntity *entity, CowlVector *annot) {
    return (CowlDeclAxiom *)cowl_get_impl_1_annot(COWL_OT_A_DECL, entity, annot);
}

/**
 * Gets the declared entity.
 *
 * @param axiom The axiom.
 * @return The entity.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
CowlEntity *cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom) {
    return (CowlEntity *)cowl_get_field(axiom, 0);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
CowlVector *cowl_decl_axiom_get_annot(CowlDeclAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
bool cowl_decl_axiom_equals(CowlDeclAxiom *lhs, CowlDeclAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
ulib_uint cowl_decl_axiom_hash(CowlDeclAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H
