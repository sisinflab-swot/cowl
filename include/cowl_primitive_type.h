/**
 * Defines the #CowlPrimitiveType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_TYPE_H
#define COWL_PRIMITIVE_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlPrimitive.
typedef cowl_enum(CowlPrimitiveType) {

/// @name Types

    /// CowlClass - class.
        COWL_PT_CLASS,

    /// CowlObjProp - object property.
        COWL_PT_OBJ_PROP,

    /// CowlDataProp - data property.
        COWL_PT_DATA_PROP,

    /// CowlAnnotProp - annotation property.
        COWL_PT_ANNOT_PROP,

    /// CowlNamedInd - named individual.
        COWL_PT_NAMED_IND,

    /// CowlDatatype - datatype.
        COWL_PT_DATATYPE,

    /// CowlAnonInd - anonymous individual.
        COWL_PT_ANON_IND,

/// @name Markers

    /// Number of enum values.
        COWL_PT_COUNT,

    /// Limit for entities.
        COWL_PT_MAX_ENTITY = COWL_PT_DATATYPE,

    /// First enum value.
        COWL_PT_FIRST = 0

} CowlPrimitiveType;

COWL_END_DECLS

#endif // COWL_PRIMITIVE_TYPE_H
