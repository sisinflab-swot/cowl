/**
 * Declares CowlDisjUnionAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DISJ_UNION_AXIOM_H
#define COWL_DISJ_UNION_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [DisjointUnion] axiom in the OWL 2 specification.
 *
 * [DisjointUnion]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Union_of_Class_Expressions
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDisjUnionAxiom
 */
cowl_struct_decl(CowlDisjUnionAxiom);

/**
 * @defgroup CowlDisjUnionAxiom CowlDisjUnionAxiom API
 * @{
 */

/**
 * Returns a disjoint union axiom.
 *
 * @param cls The class which is equivalent to the disjoint union.
 * @param disjoints The class expressions which are operands of the disjoint union.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDisjUnionAxiom *
cowl_disj_union_axiom(CowlClass *cls, CowlVector *disjoints, CowlVector *annot) {
    return (CowlDisjUnionAxiom *)cowl_get_impl_2_annot(COWL_OT_A_DISJ_UNION, cls, disjoints, annot);
}

/**
 * Gets the class which is equivalent to the disjoint union.
 *
 * @param axiom The axiom.
 * @return The class.
 */
COWL_PURE
COWL_INLINE
CowlClass *cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom) {
    return (CowlClass *)cowl_get_field(axiom, 0);
}

/**
 * Gets the class expressions which are operands of the disjoint union.
 * @param axiom The axiom.
 * @return The class expressions.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_H
