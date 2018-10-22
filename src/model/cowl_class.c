/// @author Ivano Bilenchi

#include "cowl_class_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlClassMap, CowlIRI const*, CowlClass*, cowl_iri_hash, cowl_iri_equals);
static khash_t(CowlClassMap) *inst_map = NULL;

#pragma mark - Private

static CowlClass* cowl_class_alloc(CowlIRI const *iri) {
    CowlClass init = {
        .super = COWL_CLS_EXP_INIT(CCET_CLASS, 0),
        .iri = cowl_iri_retain(iri)
    };
    CowlClass *cls = malloc(sizeof(*cls));
    memcpy(cls, &init, sizeof(*cls));

    uint32_t hash = kh_ptr_hash_func(cls);
    cowl_cls_exp_hash_set(cls, hash);

    return cls;
}

static void cowl_class_free(CowlClass const *cls) {
    if (!cls) return;
    cowl_iri_release(cls->iri);
    free((void *)cls);
}

#pragma mark - Public

CowlClass const* cowl_class_get(CowlIRI const *iri) {
    if (!inst_map) inst_map = kh_init(CowlClassMap);

    CowlClass *cls;
    bool absent;
    khint_t idx = kh_put_key(CowlClassMap, inst_map, iri, &absent);

    if (absent) {
        cls = cowl_class_alloc(iri);
        kh_value(inst_map, idx) = cls;
    } else {
        cls = kh_value(inst_map, idx);
        cowl_cls_exp_ref_incr(cls);
    }

    return cls;
}

CowlClass const* cowl_class_retain(CowlClass const *cls) {
    return cowl_cls_exp_ref_incr(cls);
}

void cowl_class_release(CowlClass const *cls) {
    if (cls && !cowl_cls_exp_ref_decr(cls)) {
        kh_del_val(CowlClassMap, inst_map, cls->iri);
        cowl_class_free(cls);
    }
}

CowlIRI const* cowl_class_get_iri(CowlClass const *cls) {
    return cls->iri;
}

bool cowl_class_equals(CowlClass const *lhs, CowlClass const *rhs) {
    return lhs == rhs;
}

uint32_t cowl_class_hash(CowlClass const *cls) {
    return cowl_cls_exp_hash_get(cls);
}

bool cowl_class_iterate_signature(CowlClass const *cls, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_init_class(cls));
}
