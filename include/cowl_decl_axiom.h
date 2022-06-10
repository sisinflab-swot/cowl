/**
 * Declares CowlDeclAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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
CowlDeclAxiom* cowl_decl_axiom_get(CowlEntity *entity, CowlVector *annot) {
    return (CowlDeclAxiom *)cowl_get_impl_1_opt(COWL_OT_A_DECL, entity, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
CowlDeclAxiom* cowl_decl_axiom_retain(CowlDeclAxiom *axiom) {
    return (CowlDeclAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
void cowl_decl_axiom_release(CowlDeclAxiom *axiom) {
    cowl_release_impl(axiom);
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
CowlEntity* cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom) {
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
CowlVector* cowl_decl_axiom_get_annot(CowlDeclAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
CowlString* cowl_decl_axiom_to_string(CowlDeclAxiom *axiom) {
    return cowl_to_string_impl(axiom);
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

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDeclAxiom
 */
COWL_INLINE
bool cowl_decl_axiom_iterate_primitives(CowlDeclAxiom *axiom, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H
