/**
 * Declares CowlDatatypeDefAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_DEF_AXIOM_H
#define COWL_DATATYPE_DEF_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDatatype);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
cowl_struct_decl(CowlDatatypeDefAxiom);
/// @endcond

/**
 * Represents a [DatatypeDefinition] axiom in the OWL 2 specification.
 *
 * [DatatypeDefinition]: https://www.w3.org/TR/owl2-syntax/#Datatype_Definitions
 *
 * @struct CowlDatatypeDefAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained datatype definition axiom.
 *
 * @param dt The defined datatype.
 * @param range Range of the defined datatype.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlDatatypeDefAxiom* cowl_datatype_def_axiom_get(CowlDatatype *dt, CowlDataRange *range,
                                                  CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlDatatypeDefAxiom* cowl_datatype_def_axiom_retain(CowlDatatypeDefAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
void cowl_datatype_def_axiom_release(CowlDatatypeDefAxiom *axiom);

/**
 * Gets the defined datatype.
 *
 * @param axiom The axiom.
 * @return The datatype.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlDatatype* cowl_datatype_def_axiom_get_datatype(CowlDatatypeDefAxiom *axiom);

/**
 * Gets the range of the defined datatype.
 * @param axiom The axiom.
 * @return The range.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlDataRange* cowl_datatype_def_axiom_get_range(CowlDatatypeDefAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_datatype_def_axiom_get_annot(CowlDatatypeDefAxiom *axiom);

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
CowlString* cowl_datatype_def_axiom_to_string(CowlDatatypeDefAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
bool cowl_datatype_def_axiom_equals(CowlDatatypeDefAxiom *lhs, CowlDatatypeDefAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
ulib_uint cowl_datatype_def_axiom_hash(CowlDatatypeDefAxiom *axiom);

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_PUBLIC
bool cowl_datatype_def_axiom_iterate_primitives(CowlDatatypeDefAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATATYPE_DEF_AXIOM_H
