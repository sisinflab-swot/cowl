/// @author Ivano Bilenchi

#ifndef COWL_ENTITY_H
#define COWL_ENTITY_H

#include "cowl_entity_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI const CowlIRI;
typedef struct CowlClass const CowlClass;
typedef struct CowlObjProp const CowlObjProp;
typedef struct CowlNamedIndividual const CowlNamedIndividual;

typedef struct CowlEntity {
    CowlEntityType type;

    union {
        CowlClass *owl_class;
        CowlObjProp *obj_prop;
        CowlNamedIndividual *named_ind;
    };

} CowlEntity;

#define cowl_entity_wrap_class(CLS) \
    ((CowlEntity const){ .type = CET_CLASS, .owl_class = (CLS) })

#define cowl_entity_wrap_obj_prop(PROP) \
    ((CowlEntity const){ .type = CET_OBJ_PROP, .obj_prop = (PROP) })

#define cowl_entity_wrap_named_individual(IND) \
    ((CowlEntity const){ .type = CET_NAMED_INDIVIDUAL, .named_ind = (IND) })

#define cowl_entity_init_class(CLS) \
    cowl_entity_wrap_class(cowl_class_retain(CLS))

#define cowl_entity_init_obj_prop(PROP) \
    cowl_entity_wrap_obj_prop(cowl_obj_prop_retain(PROP))

#define cowl_entity_init_named_individual(IND) \
    cowl_entity_wrap_named_individual(cowl_named_individual_retain(IND))

CowlEntity cowl_entity_retain(CowlEntity entity);
void cowl_entity_release(CowlEntity entity);

CowlIRI* cowl_entity_get_iri(CowlEntity entity);

bool cowl_entity_equals(CowlEntity lhs, CowlEntity rhs);
uint32_t cowl_entity_hash(CowlEntity entity);

COWL_END_DECLS

#endif // COWL_ENTITY_H
