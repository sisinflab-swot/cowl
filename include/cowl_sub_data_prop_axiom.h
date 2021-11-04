/**
 * Declares CowlSubDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SUB_DATA_PROP_AXIOM_H
#define COWL_SUB_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlSubDataPropAxiom);
/// @endcond

/**
 * Represents a [SubDataPropertyOf] axiom in the OWL 2 specification.
 *
 * [SubDataPropertyOf]: https://www.w3.org/TR/owl2-syntax/#Data_Subproperties
 *
 * @struct CowlSubDataPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained data subproperty axiom.
 *
 * @param sub The subproperty.
 * @param super The superproperty.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_get(CowlDataPropExp *sub, CowlDataPropExp *super,
                                                   CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_retain(CowlSubDataPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
void cowl_sub_data_prop_axiom_release(CowlSubDataPropAxiom *axiom);

/**
 * Gets the superproperty.
 *
 * @param axiom The axiom.
 * @return The superproperty.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlDataPropExp* cowl_sub_data_prop_axiom_get_super(CowlSubDataPropAxiom *axiom);

/**
 * Gets the subproperty.
 *
 * @param axiom The axiom.
 * @return The subproperty.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlDataPropExp* cowl_sub_data_prop_axiom_get_sub(CowlSubDataPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_sub_data_prop_axiom_get_annot(CowlSubDataPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_sub_data_prop_axiom_to_string(CowlSubDataPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_data_prop_axiom_equals(CowlSubDataPropAxiom *lhs, CowlSubDataPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_sub_data_prop_axiom_hash(CowlSubDataPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlSubDataPropAxiom
 */
COWL_PUBLIC
bool cowl_sub_data_prop_axiom_iterate_primitives(CowlSubDataPropAxiom *axiom,
                                                 CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_DATA_PROP_AXIOM_H
