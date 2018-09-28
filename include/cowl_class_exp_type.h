/** @file
 * Defines the CowlClassExpType enum.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_CLASS_EXPRESSION_TYPE_H
#define COWL_CLASS_EXPRESSION_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the different types of OWL 2 class expressions.
typedef enum CowlClassExpType {

#pragma mark - Class

    /// Represents CowlClass.
        CCET_CLASS,

#pragma mark - Object property restrictions

    /// Represents CowlObjectSomeValuesFrom.
        CCET_OBJECT_SOME_VALUES_FROM,

    /// Represents CowlObjectAllValuesFrom.
        CCET_OBJECT_ALL_VALUES_FROM,

    /// Represents CowlObjectMinCardinality.
        CCET_OBJECT_MIN_CARDINALITY,

    /// Represents CowlObjectMaxCardinality.
        CCET_OBJECT_MAX_CARDINALITY,

    /// Represents CowlObjectExactCardinality.
        CCET_OBJECT_EXACT_CARDINALITY,

    /// Represents CowlObjectHasValue.
        CCET_OBJECT_HAS_VALUE,

    /// Represents CowlObjectHasSelf.
        CCET_OBJECT_HAS_SELF,

#pragma mark - Data property restrictions

    /// Represents CowlDataSomeValuesFrom.
        CCET_DATA_SOME_VALUES_FROM,

    /// Represents CowlDataAllValuesFrom.
        CCET_DATA_ALL_VALUES_FROM,

    /// Represents CowlDataMinCardinality.
        CCET_DATA_MIN_CARDINALITY,

    /// Represents CowlDataMaxCardinality.
        CCET_DATA_MAX_CARDINALITY,

    /// Represents CowlDataExactCardinality.
        CCET_DATA_EXACT_CARDINALITY,

    /// Represents CowlDataHasValue.
        CCET_DATA_HAS_VALUE,

#pragma mark - Boolean expressions

    /// Represents CowlObjectIntersectionOf.
        CCET_OBJECT_INTERSECTION_OF,

    /// Represents CowlObjectUnionOf.
        CCET_OBJECT_UNION_OF,

    /// Represents CowlObjectComplementOf.
        CCET_OBJECT_COMPLEMENT_OF,

#pragma mark - Enumeration

    /// Represents CowlObjectOneOf.
        CCET_OBJECT_ONE_OF

} CowlClassExpType;

COWL_END_DECLS

#endif // COWL_CLASS_EXPRESSION_TYPE_H
