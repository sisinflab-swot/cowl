/// @author Ivano Bilenchi

#include "cowl_data_prop_private.h"
#include "cowl_iri_private.h"
#include "uhash.h"

UHASH_MAP_INIT(CowlDataPropMap, CowlIRI*, CowlDataProp*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlDataPropMap) *inst_map = NULL;

static CowlDataProp* cowl_data_prop_alloc(CowlIRI *iri) {
    CowlDataProp init = { .super = COWL_DATA_PROP_EXP_INIT, .iri = cowl_iri_retain(iri) };
    struct CowlDataProp *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_data_prop_free(CowlDataProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

CowlDataProp* cowl_data_prop_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlDataPropMap);

    CowlDataProp *prop;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlDataPropMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        prop = cowl_data_prop_alloc(iri);
        uhash_value(inst_map, idx) = prop;
    } else {
        prop = uhash_value(inst_map, idx);
        cowl_data_prop_exp_ref_incr(prop);
    }

    return prop;
}

CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop) {
    return cowl_data_prop_exp_ref_incr(prop);
}

void cowl_data_prop_release(CowlDataProp *prop) {
    if (prop && !cowl_data_prop_exp_ref_decr(prop)) {
        uhmap_remove(CowlDataPropMap, inst_map, prop->iri);
        cowl_data_prop_free(prop);
    }
}

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop) {
    return prop->iri;
}

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs) {
    return lhs == rhs;
}

uint32_t cowl_data_prop_hash(CowlDataProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_data_prop_iterate_signature(CowlDataProp *prop, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_data_prop(prop));
}
