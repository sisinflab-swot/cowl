/// @author Ivano Bilenchi

#include "cowl_named_individual_private.h"
#include "cowl_iri_private.h"

UHASH_MAP_INIT(CowlNamedIndividualMap, CowlIRI*, CowlNamedIndividual*,
               cowl_iri_hash, cowl_iri_equals)
static UHash(CowlNamedIndividualMap) *inst_map = NULL;

static CowlNamedIndividual* cowl_named_individual_alloc(CowlIRI *iri) {
    CowlNamedIndividual ind_init = {
        .super = COWL_INDIVIDUAL_INIT(true),
        .iri = cowl_iri_retain(iri)
    };
    struct CowlNamedIndividual *ind = malloc(sizeof(*ind));
    memcpy(ind, &ind_init, sizeof(*ind));
    return ind;
}

static void cowl_named_individual_free(CowlNamedIndividual *ind) {
    if (!ind) return;
    cowl_iri_release(ind->iri);
    free((void *)ind);
}

CowlNamedIndividual* cowl_named_individual_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlNamedIndividualMap);

    CowlNamedIndividual *ind;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlNamedIndividualMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        ind = cowl_named_individual_alloc(iri);
        uhash_value(inst_map, idx) = ind;
    } else {
        ind = uhash_value(inst_map, idx);
        cowl_individual_ref_incr(ind);
    }

    return ind;
}

CowlNamedIndividual* cowl_named_individual_retain(CowlNamedIndividual *ind) {
    return cowl_individual_ref_incr(ind);
}

void cowl_named_individual_release(CowlNamedIndividual *ind) {
    if (ind && !cowl_individual_ref_decr(ind)) {
        uhmap_remove(CowlNamedIndividualMap, inst_map, ind->iri);
        cowl_named_individual_free(ind);
    }
}

CowlIRI* cowl_named_individual_get_iri(CowlNamedIndividual *ind) {
    return ind->iri;
}

bool cowl_named_individual_equals(CowlNamedIndividual *lhs, CowlNamedIndividual *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_named_individual_hash(CowlNamedIndividual *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_named_individual_iterate_signature(CowlNamedIndividual *ind,
                                             void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_named_individual(ind));
}
