/**
 * Declares CowlSubAnnotPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_ANNOT_PROP_AXIOM_H
#define COWL_SUB_ANNOT_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlSubAnnotPropAxiom);
/// @endcond

/**
 * Represents a [SubAnnotationPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubAnnotationPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Annotation_Subproperties
 *
 * @struct CowlSubAnnotPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained annotation subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_get(CowlAnnotProp *sub, CowlAnnotProp *super,
                                                     CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_retain(CowlSubAnnotPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
void cowl_sub_annot_prop_axiom_release(CowlSubAnnotPropAxiom *axiom);

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlAnnotProp* cowl_sub_annot_prop_axiom_get_super(CowlSubAnnotPropAxiom *axiom);

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlAnnotProp* cowl_sub_annot_prop_axiom_get_sub(CowlSubAnnotPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_sub_annot_prop_axiom_get_annot(CowlSubAnnotPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_sub_annot_prop_axiom_to_string(CowlSubAnnotPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_annot_prop_axiom_equals(CowlSubAnnotPropAxiom *lhs, CowlSubAnnotPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_sub_annot_prop_axiom_hash(CowlSubAnnotPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubAnnotPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_annot_prop_axiom_iterate_primitives(CowlSubAnnotPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_ANNOT_PROP_AXIOM_H
