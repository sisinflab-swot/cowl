/**
 * Declares CowlDatatypeRestr and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_RESTR_H
#define COWL_DATATYPE_RESTR_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlDatatypeRestr);
/// @endcond

/**
 * Represents a [DatatypeRestriction] in the OWL 2 specification.
 *
 * [DatatypeRestriction]: https://www.w3.org/TR/owl2-syntax/#Datatype_Restrictions
 *
 * @struct CowlDatatypeRestr
 * @extends CowlDataRange
 */

/**
 * Returns a retained datatype restriction.
 *
 * @param datatype The datatype that this data range restricts.
 * @param restrictions Set of facet restrictions.
 * @return Retained datatype restriction, or NULL on error.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
CowlDatatypeRestr *cowl_datatype_restr(CowlDatatype *datatype, CowlVector *restrictions) {
    return (CowlDatatypeRestr *)cowl_get_impl_2(COWL_OT_DR_DATATYPE_RESTR, datatype, restrictions);
}

/**
 * Gets the datatype that this data range restricts.
 *
 * @param restr The datatype restriction.
 * @return The datatype.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
CowlDatatype *cowl_datatype_restr_get_datatype(CowlDatatypeRestr *restr) {
    return (CowlDatatype *)cowl_get_field(restr, 0);
}

/**
 * Gets the facet restrictions.
 *
 * @param restr The datatype restriction.
 * @return The facet restrictions.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
CowlVector *cowl_datatype_restr_get_restrictions(CowlDatatypeRestr *restr) {
    return (CowlVector *)cowl_get_field(restr, 1);
}

/**
 * Returns the string representation of the specified datatype restriction.
 *
 * @param restr The datatype restriction.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
CowlString *cowl_datatype_restr_to_string(CowlDatatypeRestr *restr) {
    return cowl_to_string(restr);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
bool cowl_datatype_restr_equals(CowlDatatypeRestr *lhs, CowlDatatypeRestr *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param restr The datatype restriction.
 * @return The hash value.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
ulib_uint cowl_datatype_restr_hash(CowlDatatypeRestr *restr) {
    return cowl_hash_impl(restr);
}

/**
 * Iterates over the primitives referenced by the specified datatype restriction.
 *
 * @param restr The datatype restriction.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_INLINE
bool cowl_datatype_restr_iterate_primitives(CowlDatatypeRestr *restr, CowlPrimitiveFlags flags,
                                            CowlIterator *iter) {
    return cowl_iterate_primitives_impl(restr, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_H
