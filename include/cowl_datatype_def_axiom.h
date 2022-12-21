/**
 * Declares CowlDatatypeDefAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_DEF_AXIOM_H
#define COWL_DATATYPE_DEF_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlVector);
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
COWL_INLINE
CowlDatatypeDefAxiom* cowl_datatype_def_axiom(CowlDatatype *dt, CowlAnyDataRange *range,
                                              CowlVector *annot) {
    return (CowlDatatypeDefAxiom *)cowl_get_impl_2_annot(COWL_OT_A_DATATYPE_DEF, dt, range, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
CowlDatatypeDefAxiom* cowl_datatype_def_axiom_retain(CowlDatatypeDefAxiom *axiom) {
    return (CowlDatatypeDefAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
void cowl_datatype_def_axiom_release(CowlDatatypeDefAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the defined datatype.
 *
 * @param axiom The axiom.
 * @return The datatype.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
CowlDatatype* cowl_datatype_def_axiom_get_datatype(CowlDatatypeDefAxiom *axiom) {
    return (CowlDatatype *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the defined datatype.
 * @param axiom The axiom.
 * @return The range.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
CowlDataRange* cowl_datatype_def_axiom_get_range(CowlDatatypeDefAxiom *axiom) {
    return (CowlDataRange *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
CowlVector* cowl_datatype_def_axiom_get_annot(CowlDatatypeDefAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

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
COWL_INLINE
CowlString* cowl_datatype_def_axiom_to_string(CowlDatatypeDefAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
bool cowl_datatype_def_axiom_equals(CowlDatatypeDefAxiom *lhs, CowlDatatypeDefAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDatatypeDefAxiom
 */
COWL_INLINE
ulib_uint cowl_datatype_def_axiom_hash(CowlDatatypeDefAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

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
COWL_INLINE
bool cowl_datatype_def_axiom_iterate_primitives(CowlDatatypeDefAxiom *axiom,
                                                CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATATYPE_DEF_AXIOM_H
