/// @author Ivano Bilenchi

#include "cowl_obj_prop_private.h"
#include "cowl_iri_private.h"

UHASH_MAP_INIT(CowlObjPropMap, CowlIRI*, CowlObjProp*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlObjPropMap) *inst_map = NULL;

static CowlObjProp* cowl_obj_prop_alloc(CowlIRI *iri) {
    CowlObjProp init = { .super = COWL_OBJ_PROP_EXP_INIT(false), .iri = cowl_iri_retain(iri) };
    struct CowlObjProp *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_obj_prop_free(CowlObjProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlObjPropMap);

    CowlObjProp *prop;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlObjPropMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        prop = cowl_obj_prop_alloc(iri);
        uhash_value(inst_map, idx) = prop;
    } else {
        prop = uhash_value(inst_map, idx);
        cowl_obj_prop_exp_ref_incr(prop);
    }

    return prop;
}

CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop) {
    return cowl_obj_prop_exp_ref_incr(prop);
}

void cowl_obj_prop_release(CowlObjProp *prop) {
    if (prop && !cowl_obj_prop_exp_ref_decr(prop)) {
        uhmap_remove(CowlObjPropMap, inst_map, prop->iri);
        cowl_obj_prop_free(prop);
    }
}

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop) {
    return prop->iri;
}

bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_obj_prop_hash(CowlObjProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_obj_prop_iterate_signature(CowlObjProp *prop, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_obj_prop(prop));
}
