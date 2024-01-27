/**
 * Defines the CowlClsExpType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLS_EXP_TYPE_H
#define COWL_CLS_EXP_TYPE_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Represents the type of @type{#CowlClsExp}.
typedef enum CowlClsExpType {

    /// @type{#CowlClass} - class.
    COWL_CET_CLASS,

    /// @name Object property restrictions

    /// @type{#CowlObjQuant} - "some values from" object property restriction.
    COWL_CET_OBJ_SOME,

    /// @type{#CowlObjQuant} - "all values from" object property restriction.
    COWL_CET_OBJ_ALL,

    /// @type{#CowlObjCard} - "minimum cardinality" object property restriction.
    COWL_CET_OBJ_MIN_CARD,

    /// @type{#CowlObjCard} - "maximum cardinality" object property restriction.
    COWL_CET_OBJ_MAX_CARD,

    /// @type{#CowlObjCard} - "exact cardinality" object property restriction.
    COWL_CET_OBJ_EXACT_CARD,

    /// @type{#CowlObjHasValue} - "has value" object property restriction.
    COWL_CET_OBJ_HAS_VALUE,

    /// @type{#CowlObjHasSelf} - "has self" object property restriction.
    COWL_CET_OBJ_HAS_SELF,

    /// @name Data property restrictions

    /// @type{#CowlDataQuant} - "some values from" data property restriction.
    COWL_CET_DATA_SOME,

    /// @type{#CowlDataQuant} - "all values from" data property restriction.
    COWL_CET_DATA_ALL,

    /// @type{#CowlDataCard} - "min cardinality" data property restriction.
    COWL_CET_DATA_MIN_CARD,

    /// @type{#CowlDataCard} - "max cardinality" data property restriction.
    COWL_CET_DATA_MAX_CARD,

    /// @type{#CowlDataCard} - "exact cardinality" data property restriction.
    COWL_CET_DATA_EXACT_CARD,

    /// @type{#CowlDataHasValue} - "has value" data property restriction.
    COWL_CET_DATA_HAS_VALUE,

    /// @name Boolean expressions

    /// @type{#CowlNAryBool} - Intersection of class expressions.
    COWL_CET_OBJ_INTERSECT,

    /// @type{#CowlNAryBool} - Union of class expressions.
    COWL_CET_OBJ_UNION,

    /// @type{#CowlObjCompl} - Complement of a class expression.
    COWL_CET_OBJ_COMPL,

    /// @name Enumeration

    /// @type{#CowlObjOneOf} - Enumeration of individuals.
    COWL_CET_OBJ_ONE_OF,

    /// @name Markers

    /// Number of enum values.
    COWL_CET_COUNT,

    /// First enum value.
    COWL_CET_FIRST = 0

} CowlClsExpType;

COWL_END_DECLS

#endif // COWL_CLS_EXP_TYPE_H
