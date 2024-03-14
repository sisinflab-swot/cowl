/**
 * Declares CowlAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_H
#define COWL_AXIOM_H

#include "cowl_axiom_type.h"
#include "cowl_object.h"
#include "cowl_position.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [Axiom] in the OWL 2 specification.
 *
 * [Axiom]: https://www.w3.org/TR/owl2-syntax/#Axioms
 *
 * @superstruct{CowlObject}
 * @struct CowlAxiom
 */
cowl_struct_decl(CowlAxiom);

/**
 * @defgroup CowlAxiom CowlAxiom API
 * @{
 */

/**
 * Gets the type of the specified axiom.
 *
 * @param axiom The axiom.
 * @return Axiom type.
 */
COWL_PURE
COWL_INLINE
CowlAxiomType cowl_axiom_get_type(CowlAnyAxiom *axiom) {
    return (CowlAxiomType)(cowl_get_type(axiom) - COWL_OT_A_DECL);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations, or NULL if the axiom has no annotations.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_axiom_get_annot(CowlAnyAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Checks if the axiom has the specified operand.
 *
 * @param axiom The axiom.
 * @param operand The operand.
 * @param position Position where the operand should appear.
 * @return True if the axiom has the specified operand, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_axiom_has_operand(CowlAnyAxiom *axiom, CowlAny *operand, CowlPosition position);

/**
 * Checks if the axiom has an operand with the specified IRI.
 *
 * @param axiom The axiom.
 * @param iri The IRI.
 * @param position Position where the operand should appear.
 * @return True if the axiom has an operand with the specified IRI, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_axiom_has_operand_with_iri(CowlAnyAxiom *axiom, CowlIRI *iri, CowlPosition position);

/**
 * Iterates over the operands of the specified axiom.
 *
 * @param axiom The axiom.
 * @param position Position of the desired operands.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 */
COWL_API
bool cowl_axiom_iterate_operands(CowlAnyAxiom *axiom, CowlPosition position, CowlIterator *iter);

/**
 * Checks whether the axiom references the specified primitive.
 *
 * @param axiom The axiom.
 * @param primitive The primitive.
 * @param position Position of the desired primitive.
 * @return True if the axiom references the primitive, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_axiom_has_primitive(CowlAnyAxiom *axiom, CowlAnyPrimitive *primitive,
                              CowlPosition position);

/// @}

COWL_END_DECLS

#endif // COWL_AXIOM_H
