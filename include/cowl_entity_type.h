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
    CET_CLASS,

    /// Represents CowlObjectProperty.
    CET_OBJ_PROP,

    /// Represents CowlDataProperty.
    CET_DATA_PROP,

    /// Represents CowlAnnotationProperty.
    CET_ANNOT_PROP,

    /// Represents CowlNamedInd.
    CET_NAMED_IND,

    /// Represents CowlDatatype.
    CET_DATATYPE

} CowlEntityType;

COWL_END_DECLS

#endif // COWL_ENTITY_TYPE_H
