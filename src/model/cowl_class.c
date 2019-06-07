/// @author Ivano Bilenchi

#include "cowl_class_private.h"
#include "cowl_iri_private.h"
#include "cowl_vocabulary.h"

UHASH_MAP_INIT(CowlClassMap, CowlIRI*, CowlClass*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlClassMap) *inst_map = NULL;

static CowlClass* cowl_class_alloc(CowlIRI *iri) {
    CowlClass init = {
        .super = COWL_CLS_EXP_INIT(CCET_CLASS, 0),
        .iri = cowl_iri_retain(iri)
    };
    cowl_struct(CowlClass) *cls = malloc(sizeof(*cls));
    memcpy(cls, &init, sizeof(*cls));

    cowl_uint_t hash = uhash_ptr_hash(cls);
    cowl_object_hash_set(cls, hash);

    return cls;
}

static void cowl_class_free(CowlClass *cls) {
    if (!cls) return;
    cowl_iri_release(cls->iri);
    free((void *)cls);
}

CowlClass* cowl_class_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlClassMap);

    CowlClass *cls;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlClassMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        cls = cowl_class_alloc(iri);
        uhash_value(inst_map, idx) = cls;
    } else {
        cls = uhash_value(inst_map, idx);
        cowl_object_retain(cls);
    }

    return cls;
}

CowlClass* cowl_class_retain(CowlClass *cls) {
    return cowl_object_retain(cls);
}

void cowl_class_release(CowlClass *cls) {
    if (cls && !cowl_object_release(cls)) {
        uhmap_remove(CowlClassMap, inst_map, cls->iri);
        cowl_class_free(cls);
    }
}

CowlIRI* cowl_class_get_iri(CowlClass *cls) {
    return cls->iri;
}

bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_class_hash(CowlClass *cls) {
    return cowl_object_hash_get(cls);
}

bool cowl_class_iterate_signature(CowlClass *cls, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_class(cls));
}
