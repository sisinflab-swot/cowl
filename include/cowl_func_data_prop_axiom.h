/**
 * Declares CowlFuncDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FUNC_DATA_PROP_AXIOM_H
#define COWL_FUNC_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlFuncDataPropAxiom);
/// @endcond

/**
 * Represents a [FunctionalDataProperty] axiom in the OWL 2 Specification.
 *
 * [FunctionalDataProperty]: https://www.w3.org/TR/owl2-syntax/#Functional_Data_Properties
 *
 * @struct CowlFuncDataPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained functional data property axiom.
 *
 * @param prop The data property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_get(CowlDataPropExp *prop,
                                                     CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_retain(CowlFuncDataPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
void cowl_func_data_prop_axiom_release(CowlFuncDataPropAxiom *axiom);

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
CowlDataPropExp* cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_func_data_prop_axiom_get_annot(CowlFuncDataPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_func_data_prop_axiom_to_string(CowlFuncDataPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
bool cowl_func_data_prop_axiom_equals(CowlFuncDataPropAxiom *lhs, CowlFuncDataPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_func_data_prop_axiom_hash(CowlFuncDataPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlFuncDataPropAxiom
 */
COWL_PUBLIC
bool cowl_func_data_prop_axiom_iterate_primitives(CowlFuncDataPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_FUNC_DATA_PROP_AXIOM_H
