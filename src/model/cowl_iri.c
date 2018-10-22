/// @author Ivano Bilenchi

#include <string.h>

#include "cowl_iri_private.h"
#include "cowl_hash_utils.h"
#include "cowl_string.h"
#include "khash_utils.h"

#pragma mark - Instance map

static inline uint32_t cowl_iri_map_hash_func(CowlIRI iri) {
    return cowl_hash_2(COWL_HASH_INIT_IRI,
                       cowl_string_hash(iri.ns),
                       cowl_string_hash(iri.rem));
}

static inline bool cowl_iri_map_hash_equal(CowlIRI a, CowlIRI b) {
    return cowl_string_equals(a.ns, b.ns) && cowl_string_equals(a.rem, b.rem);
}

KHASH_MAP_UTILS_INIT(CowlIRIMap, struct CowlIRI, CowlIRI*,
                     cowl_iri_map_hash_func, cowl_iri_map_hash_equal);
static khash_t(CowlIRIMap) *inst_map = NULL;

#pragma mark - Private

static struct CowlIRI* cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI init = COWL_IRI_INIT(cowl_string_retain(ns), cowl_string_retain(rem));
    struct CowlIRI *iri = malloc(sizeof(*iri));
    memcpy(iri, &init, sizeof(*iri));
    return iri;
}

static void cowl_iri_free(CowlIRI *iri) {
    if (!iri) return;
    cowl_string_release((CowlString *)iri->ns);
    cowl_string_release((CowlString *)iri->rem);
    free((void *)iri);
}

#pragma mark - Public

CowlIRI* cowl_iri_get(CowlString *ns, CowlString *rem) {
    if (!inst_map) inst_map = kh_init(CowlIRIMap);

    CowlIRI key = { .ns = ns, .rem = rem };
    CowlIRI *iri;

    bool absent;
    khint_t idx = kh_put_key(CowlIRIMap, inst_map, key, &absent);

    if (absent) {
        iri = cowl_iri_alloc(ns, rem);
        kh_value(inst_map, idx) = iri;
    } else {
        iri = kh_value(inst_map, idx);
        cowl_iri_ref_incr(iri);
    }

    return iri;
}

CowlIRI* cowl_iri_retain(CowlIRI *iri) {
    return cowl_iri_ref_incr(iri);
}

void cowl_iri_release(CowlIRI *iri) {
    if (iri && !cowl_iri_ref_decr(iri)) {
        kh_del_val(CowlIRIMap, inst_map, (*iri));
        cowl_iri_free(iri);
    }
}

CowlString* cowl_iri_get_ns(CowlIRI *iri) {
    return iri->ns;
}

CowlString* cowl_iri_get_rem(CowlIRI *iri) {
    return iri->rem;
}

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs) {
    return lhs == rhs;
}

uint32_t cowl_iri_hash(CowlIRI *iri) {
    return kh_ptr_hash_func(iri);
}
