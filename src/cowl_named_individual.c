/// @author Ivano Bilenchi

#include "cowl_named_individual_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

CowlIRI const* cowl_named_individual_get_iri(CowlNamedIndividual const *ind) {
    return ind->iri;
}

bool cowl_named_individual_equals(CowlNamedIndividual const *lhs, CowlNamedIndividual const *rhs) {
    return cowl_iri_equals(lhs->iri, rhs->iri);
}

uint32_t cowl_named_individual_hash(CowlNamedIndividual const *ind) {
    return cowl_hash_1(COWL_HASH_INIT_NAMED_INDIVIDUAL, cowl_iri_hash(ind->iri));
}

bool cowl_named_individual_iterate_signature(CowlNamedIndividual const *ind,
                                             void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_init_named_individual(ind));
}
