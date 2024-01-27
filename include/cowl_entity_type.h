/**
 * Defines the CowlEntityType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ENTITY_TYPE_H
#define COWL_ENTITY_TYPE_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Represents the type of @type{#CowlEntity}.
typedef enum CowlEntityType {

    /// @name Types

    /// @type{#CowlClass} - class.
    COWL_ET_CLASS,

    /// @type{#CowlObjProp} - object property.
    COWL_ET_OBJ_PROP,

    /// @type{#CowlDataProp} - data property.
    COWL_ET_DATA_PROP,

    /// @type{#CowlAnnotProp} - annotation property.
    COWL_ET_ANNOT_PROP,

    /// @type{#CowlNamedInd} - named individual.
    COWL_ET_NAMED_IND,

    /// @type{#CowlDatatype} - datatype.
    COWL_ET_DATATYPE,

    /// @name Markers

    /// Number of enum values.
    COWL_ET_COUNT,

    /// First enum value.
    COWL_ET_FIRST = 0

} CowlEntityType;

COWL_END_DECLS

#endif // COWL_ENTITY_TYPE_H
