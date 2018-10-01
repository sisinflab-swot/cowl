/// @author Ivano Bilenchi

#include "cowl_entity_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

CowlEntityType cowl_entity_type(CowlEntity const *entity) {
    return entity->type;
}

CowlIRI const* cowl_entity_iri(CowlEntity const *entity) {
    return entity->iri;
}

bool cowl_entity_equals(CowlEntity const *a, CowlEntity const *b) {
    return (a->type == b->type && cowl_iri_equals(a->iri, b->iri));
}

uint32_t cowl_entity_hash(CowlEntity const *entity) {
    return cowl_hash_2(COWL_HASH_INIT_ENTITY,
                       entity->type,
                       cowl_iri_hash(entity->iri));
}
