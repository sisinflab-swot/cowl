/// @author Ivano Bilenchi

#include "cowl_class_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"
#include "cowl_vocabulary.h"
#include "khash_utils.h"

KHASH_MAP_UTILS_INIT(CowlClassMap, CowlIRI*, CowlClass*, cowl_iri_hash, cowl_iri_equals);
static khash_t(CowlClassMap) *inst_map = NULL;

static CowlClass* cowl_class_alloc(CowlIRI *iri) {
    CowlClass init = {
        .super = COWL_CLS_EXP_INIT(CCET_CLASS, 0),
        .iri = cowl_iri_retain(iri)
    };
    struct CowlClass *cls = malloc(sizeof(*cls));
    memcpy(cls, &init, sizeof(*cls));

    uint32_t hash = kh_ptr_hash_func(cls);
    cowl_cls_exp_hash_set(cls, hash);

    return cls;
}

static void cowl_class_free(CowlClass *cls) {
    if (!cls) return;
    cowl_iri_release(cls->iri);
    free((void *)cls);
}

CowlClass* cowl_class_get(CowlIRI *iri) {
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

CowlClass* cowl_class_retain(CowlClass *cls) {
    return cowl_cls_exp_ref_incr(cls);
}

void cowl_class_release(CowlClass *cls) {
    if (cls && !cowl_cls_exp_ref_decr(cls)) {
        kh_del_val(CowlClassMap, inst_map, cls->iri);
        cowl_class_free(cls);
    }
}

CowlIRI* cowl_class_get_iri(CowlClass *cls) {
    return cls->iri;
}

bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs) {
    return lhs == rhs;
}

uint32_t cowl_class_hash(CowlClass *cls) {
    return cowl_cls_exp_hash_get(cls);
}

bool cowl_class_iterate_signature(CowlClass *cls, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_class(cls));
}
