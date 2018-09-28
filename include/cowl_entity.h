/// @author Ivano Bilenchi

#ifndef COWL_ENTITY_H
#define COWL_ENTITY_H

#include "cowl_entity_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI CowlIRI;

typedef struct CowlEntity CowlEntity;

CowlEntityType cowl_entity_type(CowlEntity const *entity);
CowlIRI const* cowl_entity_iri(CowlEntity const *entity);

bool cowl_entity_equals(CowlEntity const *a, CowlEntity const *b);
uint32_t cowl_entity_hash(CowlEntity const *entity);

COWL_END_DECLS

#endif // COWL_ENTITY_H
