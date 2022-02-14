/**
 * Defines the #CowlEntityType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ENTITY_TYPE_H
#define COWL_ENTITY_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlEntity.
typedef enum CowlEntityType {

/// @name Types

    /// CowlClass - class.
    COWL_ET_CLASS,

    /// CowlObjProp - object property.
    COWL_ET_OBJ_PROP,

    /// CowlDataProp - data property.
    COWL_ET_DATA_PROP,

    /// CowlAnnotProp - annotation property.
    COWL_ET_ANNOT_PROP,

    /// CowlNamedInd - named individual.
    COWL_ET_NAMED_IND,

    /// CowlDatatype - datatype.
    COWL_ET_DATATYPE,

/// @name Markers

    /// Number of enum values.
    COWL_ET_COUNT,

    /// First enum value.
    COWL_ET_FIRST = 0

} CowlEntityType;

COWL_END_DECLS

#endif // COWL_ENTITY_TYPE_H
