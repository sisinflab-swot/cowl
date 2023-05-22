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
cowl_struct_decl(CowlSubClsAxiom);
/// @endcond

/**
 * Represents a [SubClassOf] axiom in the OWL 2 specification.
 *
 * [SubClassOf]: https://www.w3.org/TR/owl2-syntax/#Subclass_Axioms
 *
 * @struct CowlSubClsAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained subclass axiom.
 *
 * @param sub The subclass.
 * @param super The superclass.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
CowlSubClsAxiom *cowl_sub_cls_axiom(CowlAnyClsExp *sub, CowlAnyClsExp *super, CowlVector *annot) {
    return (CowlSubClsAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_CLASS, sub, super, annot);
}

/**
 * Gets the subclass.
 *
 * @param axiom The axiom.
 * @return The subclass.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
CowlClsExp *cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the superclass.
 *
 * @param axiom The axiom.
 * @return The superclass.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
CowlClsExp *cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
CowlVector *cowl_sub_cls_axiom_get_annot(CowlSubClsAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom *lhs, CowlSubClsAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubClsAxiom
 */
COWL_INLINE
ulib_uint cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
