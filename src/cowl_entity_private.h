/// @author Ivano Bilenchi

#ifndef COWL_ENTITY_PRIVATE_H
#define COWL_ENTITY_PRIVATE_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity {
    CowlEntityType type;
    CowlIRI *iri;
} CowlEntity;

COWL_END_DECLS

#endif // COWL_ENTITY_PRIVATE_H
