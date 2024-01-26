/**
 * Declares CowlDataCompl and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_COMPL_H
#define COWL_DATA_COMPL_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
/// @endcond

/**
 * Represents [DataComplementOf] the OWL 2 specification.
 *
 * [DataComplementOf]: https://www.w3.org/TR/owl2-syntax/#Complement_of_Data_Ranges
 *
 * @superstruct{CowlDataRange}
 * @struct CowlDataCompl
 */
cowl_struct_decl(CowlDataCompl);

/**
 * @defgroup CowlDataCompl CowlDataCompl API
 * @{
 */

/**
 * Returns the complement of a data range.
 *
 * @param operand The data range which this data range is a complement of.
 * @return Data range complement, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataCompl *cowl_data_compl(CowlAnyDataRange *operand) {
    return (CowlDataCompl *)cowl_get_impl_1(COWL_OT_DR_DATA_COMPL, operand);
}

/**
 * Gets the data range which this data range is a complement of.
 *
 * @param range The data range complement.
 * @return The operand.
 */
COWL_PURE
COWL_INLINE
CowlDataRange *cowl_data_compl_get_operand(CowlDataCompl *range) {
    return (CowlDataRange *)cowl_get_field(range, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_COMPL_H
