/// @author Ivano Bilenchi

#include "cowl_annot_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

UHASH_MAP_INIT(CowlAnnotPropMap, CowlIRI*, CowlAnnotProp*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlAnnotPropMap) *inst_map = NULL;

static CowlAnnotProp* cowl_annot_prop_alloc(CowlIRI *iri) {
    CowlAnnotProp init = COWL_ANNOT_PROP_INIT(cowl_iri_retain(iri));
    cowl_struct(CowlAnnotProp) *prop = malloc(sizeof(*prop));
    memcpy(prop, &init, sizeof(*prop));
    return prop;
}

static void cowl_annot_prop_free(CowlAnnotProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    free((void *)prop);
}

CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlAnnotPropMap);

    CowlAnnotProp *prop;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlAnnotPropMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        prop = cowl_annot_prop_alloc(iri);
        uhash_value(inst_map, idx) = prop;
    } else {
        prop = uhash_value(inst_map, idx);
        cowl_annot_prop_ref_incr(prop);
    }

    return prop;
}

CowlAnnotProp* cowl_annot_prop_retain(CowlAnnotProp *prop) {
    return cowl_annot_prop_ref_incr(prop);
}

void cowl_annot_prop_release(CowlAnnotProp *prop) {
    if (prop && !cowl_annot_prop_ref_decr(prop)) {
        uhmap_remove(CowlAnnotPropMap, inst_map, prop->iri);
        cowl_annot_prop_free(prop);
    }
}

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return prop->iri;
}

bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_annot_prop_hash(CowlAnnotProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_annot_prop_iterate_signature(CowlAnnotProp *prop, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_annot_prop(prop));
}