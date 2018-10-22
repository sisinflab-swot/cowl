/// @author Ivano Bilenchi

#include "cowl_obj_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlObjPropMap, CowlIRI const*, CowlObjProp*, cowl_iri_hash, cowl_iri_equals);
static khash_t(CowlObjPropMap) *inst_map = NULL;

#pragma mark - Private

static CowlObjProp* cowl_obj_prop_alloc(CowlIRI const *iri) {
    CowlObjProp init = { .super = COWL_OBJ_PROP_EXP_INIT(false), .iri = cowl_iri_retain(iri) };
    CowlObjProp *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_obj_prop_free(CowlObjProp const *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

#pragma mark - Public

CowlObjProp const* cowl_obj_prop_get(CowlIRI const *iri) {
    if (!inst_map) inst_map = kh_init(CowlObjPropMap);

    CowlObjProp *prop;
    bool absent;
    khint_t idx = kh_put_key(CowlObjPropMap, inst_map, iri, &absent);

    if (absent) {
        prop = cowl_obj_prop_alloc(iri);
        kh_value(inst_map, idx) = prop;
    } else {
        prop = kh_value(inst_map, idx);
        cowl_obj_prop_exp_ref_incr(prop);
    }

    return prop;
}

CowlObjProp const* cowl_obj_prop_retain(CowlObjProp const *prop) {
    return cowl_obj_prop_exp_ref_incr(prop);
}

void cowl_obj_prop_release(CowlObjProp const *prop) {
    if (prop && !cowl_obj_prop_exp_ref_decr(prop)) {
        kh_del_val(CowlObjPropMap, inst_map, prop->iri);
        cowl_obj_prop_free(prop);
    }
}

CowlIRI const* cowl_obj_prop_get_iri(CowlObjProp const *prop) {
    return prop->iri;
}

bool cowl_obj_prop_equals(CowlObjProp const *lhs, CowlObjProp const *rhs) {
    return lhs == rhs;
}

uint32_t cowl_obj_prop_hash(CowlObjProp const *prop) {
    return kh_ptr_hash_func(prop);
}

bool cowl_obj_prop_iterate_signature(CowlObjProp const *prop, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_init_obj_prop(prop));
}