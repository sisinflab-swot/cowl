/**
 * Defines the #CowlCardType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CARD_TYPE_H
#define COWL_CARD_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlObjCard and CowlDataCard.
typedef enum CowlCardType {

/// @name Types

    /// Minimum cardinality.
    COWL_CT_MIN,

    /// Maximum cardinality.
    COWL_CT_MAX,

    /// Exact cardinality.
    COWL_CT_EXACT,

/// @name Markers

    /// Number of enum values.
    COWL_CT_COUNT,

    /// First enum value.
    COWL_CT_FIRST = 0

} CowlCardType;

COWL_END_DECLS

#endif // COWL_CARD_TYPE_H
