/**
 * Declares CowlNAryIndAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_IND_AXIOM_H
#define COWL_NARY_IND_AXIOM_H

#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [SameIndividuals] or [DifferentIndividuals] axiom in the OWL 2 specification.
 *
 * [SameIndividuals]: https://www.w3.org/TR/owl2-syntax/#Individual_Equality
 * [DifferentIndividuals]: https://www.w3.org/TR/owl2-syntax/#Individual_Inequality
 *
 * @superstruct{CowlAxiom}
 * @struct CowlNAryIndAxiom
 */
cowl_struct_decl(CowlNAryIndAxiom);

/**
 * @defgroup CowlNAryIndAxiom CowlNAryIndAxiom API
 * @{
 */

/**
 * Returns a N-ary individual axiom.
 *
 * @param type The type.
 * @param individuals The individuals.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryIndAxiom *
cowl_nary_ind_axiom(CowlNAryAxiomType type, CowlVector *individuals, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_SAME_IND + (CowlObjectType)type);
    return (CowlNAryIndAxiom *)cowl_get_impl_1_annot(t, individuals, annot);
}

/**
 * Gets the type of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_SAME_IND);
}

/**
 * Gets the individuals of the specified N-ary individual axiom.
 *
 * @param axiom The axiom.
 * @return The individuals.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_ind_axiom_get_individuals(CowlNAryIndAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_IND_AXIOM_H
