/**
 * Declares CowlSubClsAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_CLS_AXIOM_H
#define COWL_SUB_CLS_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [SubClassOf] axiom in the OWL 2 specification.
 *
 * [SubClassOf]: https://www.w3.org/TR/owl2-syntax/#Subclass_Axioms
 *
 * @superstruct{CowlAxiom}
 * @struct CowlSubClsAxiom
 */
cowl_struct_decl(CowlSubClsAxiom);

/**
 * @defgroup CowlSubClsAxiom CowlSubClsAxiom API
 * @{
 */

/**
 * Returns a subclass axiom.
 *
 * @param sub The subclass.
 * @param super The superclass.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlSubClsAxiom *cowl_sub_cls_axiom(CowlAnyClsExp *sub, CowlAnyClsExp *super, CowlVector *annot) {
    return (CowlSubClsAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_CLASS, sub, super, annot);
}

/**
 * Gets the subclass.
 *
 * @param axiom The axiom.
 * @return The subclass.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the superclass.
 *
 * @param axiom The axiom.
 * @return The superclass.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
