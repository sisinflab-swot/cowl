/**
 * Declares CowlNAryClsAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_CLS_AXIOM_H
#define COWL_NARY_CLS_AXIOM_H

#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [EquivalentClasses] or [DisjointClasses] axiom in the OWL 2 specification.
 *
 * [EquivalentClasses]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Classes
 * [DisjointClasses]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Classes
 *
 * @superstruct{CowlAxiom}
 * @struct CowlNAryClsAxiom
 */
cowl_struct_decl(CowlNAryClsAxiom);

/**
 * @defgroup CowlNAryClsAxiom CowlNAryClsAxiom API
 * @{
 */

/**
 * Returns a N-ary class expression axiom.
 *
 * @param type N-ary class expression axiom type.
 * @param classes The classes.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryClsAxiom *
cowl_nary_cls_axiom(CowlNAryAxiomType type, CowlVector *classes, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_EQUIV_CLASSES + (CowlObjectType)type);
    return (CowlNAryClsAxiom *)cowl_get_impl_1_annot(t, classes, annot);
}

/**
 * Gets the type of the specified N-ary class expression axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_CLASSES);
}

/**
 * Gets the classes of the specified N-ary class expression axiom.
 *
 * @param axiom The axiom.
 * @return The classes.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_CLS_AXIOM_H
