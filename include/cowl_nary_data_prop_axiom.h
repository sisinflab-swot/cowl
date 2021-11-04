/**
 * Declares CowlNAryDataPropAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_PROP_AXIOM_H
#define COWL_NARY_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlNAryDataPropAxiom);
/// @endcond

/**
 * Represents an [EquivalentDataProperties] or [DisjointDataProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentDataProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Data_Properties
 * [DisjointDataProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Data_Properties
 *
 * @struct CowlNAryDataPropAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained N-ary data property axiom.
 *
 * @param type The type.
 * @param props The data properties.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlObjectTable *props,
                                                     CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_retain(CowlNAryDataPropAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
void cowl_nary_data_prop_axiom_release(CowlNAryDataPropAxiom *axiom);

/**
 * Gets the type of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom);

/**
 * Gets the data properties of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The data properties.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlObjectTable* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_nary_data_prop_axiom_get_annot(CowlNAryDataPropAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
CowlString* cowl_nary_data_prop_axiom_to_string(CowlNAryDataPropAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
ulib_uint cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlNAryDataPropAxiom
 */
COWL_PUBLIC
bool cowl_nary_data_prop_axiom_iterate_primitives(CowlNAryDataPropAxiom *axiom,
                                                  CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_DATA_PROP_AXIOM_H
