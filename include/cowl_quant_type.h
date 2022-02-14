/**
 * Defines the #CowlQuantType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_QUANT_TYPE_H
#define COWL_QUANT_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlObjQuant and CowlDataQuant.
typedef enum CowlQuantType {

/// @name Types

    /// Existential quantifier (SomeValuesFrom).
        COWL_QT_SOME,

    /// Universal quantifier (AllValuesFrom).
        COWL_QT_ALL,

/// @name Markers

    /// Number of enum values.
        COWL_QT_COUNT,

    /// First enum value.
        COWL_QT_FIRST = 0

} CowlQuantType;

COWL_END_DECLS

#endif // COWL_QUANT_TYPE_H
