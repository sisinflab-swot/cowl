/// @author Ivano Bilenchi

#include "cowl_named_individual_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlNamedIndividualMap, CowlIRI*, CowlNamedIndividual*,
                     cowl_iri_hash, cowl_iri_equals);
static khash_t(CowlNamedIndividualMap) *inst_map = NULL;

#pragma mark - Private

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

#pragma mark - Public

CowlNamedIndividual* cowl_named_individual_get(CowlIRI *iri) {
    if (!inst_map) inst_map = kh_init(CowlNamedIndividualMap);

    CowlNamedIndividual *ind;
    bool absent;
    khint_t idx = kh_put_key(CowlNamedIndividualMap, inst_map, iri, &absent);

    if (absent) {
        ind = cowl_named_individual_alloc(iri);
        kh_value(inst_map, idx) = ind;
    } else {
        ind = kh_value(inst_map, idx);
        cowl_individual_ref_incr(ind);
    }

    return ind;
}

CowlNamedIndividual* cowl_named_individual_retain(CowlNamedIndividual *ind) {
    return cowl_individual_ref_incr(ind);
}

void cowl_named_individual_release(CowlNamedIndividual *ind) {
    if (ind && !cowl_individual_ref_decr(ind)) {
        kh_del_val(CowlNamedIndividualMap, inst_map, ind->iri);
        cowl_named_individual_free(ind);
    }
}

CowlIRI* cowl_named_individual_get_iri(CowlNamedIndividual *ind) {
    return ind->iri;
}

bool cowl_named_individual_equals(CowlNamedIndividual *lhs, CowlNamedIndividual *rhs) {
    return lhs == rhs;
}

uint32_t cowl_named_individual_hash(CowlNamedIndividual *ind) {
    return kh_ptr_hash_func(ind);
}

bool cowl_named_individual_iterate_signature(CowlNamedIndividual *ind,
                                             void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_init_named_individual(ind));
}
