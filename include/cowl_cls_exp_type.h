/** @file
 * Defines the CowlClsExpType enum.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_CLS_EXP_TYPE_H
#define COWL_CLS_EXP_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the different types of OWL 2 class expressions.
typedef enum CowlClsExpType {

/// @name Class

    /// Represents classes.
        CCET_CLASS,

/// @name Object property restrictions

    /// Represents "some values from" object property restrictions.
        CCET_OBJ_SOME,

    /// Represents "all values from" object property restrictions.
        CCET_OBJ_ALL,

    /// Represents "min cardinality" object property restrictions.
        CCET_OBJ_MIN_CARD,

    /// Represents "max cardinality" object property restrictions.
        CCET_OBJ_MAX_CARD,

    /// Represents "exact cardinality" object property restrictions.
        CCET_OBJ_EXACT_CARD,

    /// Represents "has value" object property restrictions.
        CCET_OBJ_HAS_VALUE,

    /// Represents "has self" object property restrictions.
        CCET_OBJ_HAS_SELF,

/// @name Data property restrictions

    /// Represents "some values from" data property restrictions.
        CCET_DATA_SOME,

    /// Represents "all values from" data property restrictions.
        CCET_DATA_ALL,

    /// Represents "min cardinality" data property restrictions.
        CCET_DATA_MIN_CARD,

    /// Represents "max cardinality" data property restrictions.
        CCET_DATA_MAX_CARD,

    /// Represents "exact cardinality" data property restrictions.
        CCET_DATA_EXACT_CARD,

    /// Represents "has value" data property restrictions.
        CCET_DATA_HAS_VALUE,

/// @name Boolean expressions

    /// Represents the intersection of class expressions.
        CCET_OBJ_INTERSECTION,

    /// Represents the union of class expressions.
        CCET_OBJ_UNION,

    /// Represents the complement of a class expression.
        CCET_OBJ_COMPLEMENT,

/// @name Enumeration

    /// Represents enumerations of individuals.
        CCET_OBJ_ONE_OF

} CowlClsExpType;

COWL_END_DECLS

#endif // COWL_CLS_EXP_TYPE_H
