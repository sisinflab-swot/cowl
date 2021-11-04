/**
 * Declares CowlDatatypeRestr and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_RESTR_H
#define COWL_DATATYPE_RESTR_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_hash_decl(CowlObjectTable);
cowl_struct_decl(CowlDatatype);
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
COWL_PUBLIC
CowlDatatypeRestr* cowl_datatype_restr_get(CowlDatatype *datatype, CowlObjectTable *restrictions);

/**
 * Retains the specified datatype restriction.
 *
 * @param restr The restriction.
 * @return Retained datatype restriction.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
CowlDatatypeRestr* cowl_datatype_restr_retain(CowlDatatypeRestr *restr);

/**
 * Releases the specified datatype restriction.
 *
 * @param restr The datatype restriction.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
void cowl_datatype_restr_release(CowlDatatypeRestr *restr);

/**
 * Gets the datatype that this data range restricts.
 *
 * @param restr The datatype restriction.
 * @return The datatype.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
CowlDatatype* cowl_datatype_restr_get_datatype(CowlDatatypeRestr *restr);

/**
 * Gets the facet restrictions.
 *
 * @param restr The datatype restriction.
 * @return The facet restrictions.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
CowlObjectTable* cowl_datatype_restr_get_restrictions(CowlDatatypeRestr *restr);

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
COWL_PUBLIC
CowlString* cowl_datatype_restr_to_string(CowlDatatypeRestr *restr);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
bool cowl_datatype_restr_equals(CowlDatatypeRestr *lhs, CowlDatatypeRestr *rhs);

/**
 * Hash function.
 *
 * @param restr The datatype restriction.
 * @return The hash value.
 *
 * @public @memberof CowlDatatypeRestr
 */
COWL_PUBLIC
ulib_uint cowl_datatype_restr_hash(CowlDatatypeRestr *restr);

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
COWL_PUBLIC
bool cowl_datatype_restr_iterate_primitives(CowlDatatypeRestr *restr, CowlPrimitiveFlags flags,
                                            CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_H
