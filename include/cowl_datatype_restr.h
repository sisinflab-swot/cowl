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
/// @endcond

/**
 * Represents a [DatatypeRestriction] in the OWL 2 specification.
 *
 * [DatatypeRestriction]: https://www.w3.org/TR/owl2-syntax/#Datatype_Restrictions
 *
 * @superstruct{CowlDataRange}
 * @struct CowlDatatypeRestr
 */
cowl_struct_decl(CowlDatatypeRestr);

/**
 * @defgroup CowlDatatypeRestr CowlDatatypeRestr API
 * @{
 */

/**
 * Returns a datatype restriction.
 *
 * @param datatype The datatype that this data range restricts.
 * @param restrictions Set of facet restrictions.
 * @return Datatype restriction, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDatatypeRestr *cowl_datatype_restr(CowlDatatype *datatype, CowlVector *restrictions) {
    return (CowlDatatypeRestr *)cowl_get_impl_2(COWL_OT_DR_DATATYPE_RESTR, datatype, restrictions);
}

/**
 * Gets the datatype that this data range restricts.
 *
 * @param restr The datatype restriction.
 * @return The datatype.
 */
COWL_PURE
COWL_INLINE
CowlDatatype *cowl_datatype_restr_get_datatype(CowlDatatypeRestr *restr) {
    return (CowlDatatype *)cowl_get_field(restr, 0);
}

/**
 * Gets the facet restrictions.
 *
 * @param restr The datatype restriction.
 * @return The facet restrictions.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_datatype_restr_get_restrictions(CowlDatatypeRestr *restr) {
    return (CowlVector *)cowl_get_field(restr, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_H
