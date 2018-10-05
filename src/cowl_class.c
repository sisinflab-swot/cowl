/// @author Ivano Bilenchi

#include "cowl_class_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"

CowlIRI const* cowl_class_get_iri(CowlClass const *cls) {
    return cls->iri;
}

bool cowl_class_equals(CowlClass const *lhs, CowlClass const *rhs) {
    return cowl_iri_equals(lhs->iri, rhs->iri);
}

uint32_t cowl_class_hash(CowlClass const *cls) {
    return cowl_hash_1(COWL_HASH_INIT_CLASS, cowl_iri_hash(cls->iri));
}

bool cowl_class_iterate_signature(CowlClass const *cls, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_init_class(cls));
}
