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

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_H
