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
    CET_OBJECT_PROPERTY,

    /// Represents CowlDataProperty.
    CET_DATA_PROPERTY,

    /// Represents CowlAnnotationProperty.
    CET_ANNOTATION_PROPERTY,

    /// Represents CowlNamedIndividual.
    CET_NAMED_INDIVIDUAL,

    /// Represents CowlDatatype.
    CET_DATATYPE

} CowlEntityType;

COWL_END_DECLS

#endif // COWL_ENTITY_TYPE_H
