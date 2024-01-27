/**
 * Defines the CowlPrimitiveType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_TYPE_H
#define COWL_PRIMITIVE_TYPE_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Represents the type of @type{#CowlPrimitive}.
typedef enum CowlPrimitiveType {

    /// @name Types

    /// @type{#CowlClass} - class.
    COWL_PT_CLASS,

    /// @type{#CowlObjProp} - object property.
    COWL_PT_OBJ_PROP,

    /// @type{#CowlDataProp} - data property.
    COWL_PT_DATA_PROP,

    /// @type{#CowlAnnotProp} - annotation property.
    COWL_PT_ANNOT_PROP,

    /// @type{#CowlNamedInd} - named individual.
    COWL_PT_NAMED_IND,

    /// @type{#CowlAnonInd} - anonymous individual.
    COWL_PT_ANON_IND,

    /// @type{#CowlDatatype} - datatype.
    COWL_PT_DATATYPE,

    /// @type{#CowlIRI} - IRI.
    COWL_PT_IRI,

    /// @name Markers

    /// Number of enum values.
    COWL_PT_COUNT,

    /// First enum value.
    COWL_PT_FIRST = 0

} CowlPrimitiveType;

COWL_END_DECLS

#endif // COWL_PRIMITIVE_TYPE_H
