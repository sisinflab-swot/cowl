/** @file
 * Defines the CowlEntityType enum.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_ENTITY_TYPE_H
#define COWL_ENTITY_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the different types of OWL 2 Entities.
typedef enum CowlEntityType {

    /// Represents CowlClass.
    COWL_ET_CLASS,

    /// Represents CowlObjectProperty.
    COWL_ET_OBJ_PROP,

    /// Represents CowlDataProperty.
    COWL_ET_DATA_PROP,

    /// Represents CowlAnnotationProperty.
    COWL_ET_ANNOT_PROP,

    /// Represents CowlNamedInd.
    COWL_ET_NAMED_IND,

    /// Represents CowlDatatype.
    COWL_ET_DATATYPE,

    COWL_ET_COUNT,
    COWL_ET_FIRST = COWL_ET_CLASS

} CowlEntityType;

COWL_END_DECLS

#endif // COWL_ENTITY_TYPE_H
