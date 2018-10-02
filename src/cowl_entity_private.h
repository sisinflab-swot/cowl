/// @author Ivano Bilenchi

#ifndef COWL_ENTITY_PRIVATE_H
#define COWL_ENTITY_PRIVATE_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity {
    CowlEntityType type;
    union {
        CowlClass const *owl_class;
        CowlObjProp const *obj_prop;
        CowlNamedIndividual const *named_ind;
    };
} CowlEntity;

COWL_END_DECLS

#endif // COWL_ENTITY_PRIVATE_H
