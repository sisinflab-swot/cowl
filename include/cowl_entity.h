/// @author Ivano Bilenchi

#ifndef COWL_ENTITY_H
#define COWL_ENTITY_H

#include "cowl_entity_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI CowlIRI;
typedef struct CowlClass CowlClass;
typedef struct CowlObjProp CowlObjProp;
typedef struct CowlNamedIndividual CowlNamedIndividual;

typedef struct CowlEntity CowlEntity;

CowlEntityType cowl_entity_get_type(CowlEntity const *entity);
CowlIRI const* cowl_entity_get_iri(CowlEntity const *entity);

CowlClass const* cowl_entity_as_class(CowlEntity const *entity);
CowlObjProp const* cowl_entity_as_prop(CowlEntity const *entity);
CowlNamedIndividual const* cowl_entity_as_individual(CowlEntity const *entity);

bool cowl_entity_equals(CowlEntity const *lhs, CowlEntity const *rhs);
uint32_t cowl_entity_hash(CowlEntity const *entity);

COWL_END_DECLS

#endif // COWL_ENTITY_H
