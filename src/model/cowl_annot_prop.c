/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlAnnotPropTable, CowlAnnotProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlAnnotPropTable) *inst_tbl = NULL;

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
    if (!inst_tbl) inst_tbl = uhset_alloc(CowlAnnotPropTable);

    uhash_ret_t ret;
    CowlAnnotProp key = { .iri = iri };
    uhash_uint_t idx = uhash_put(CowlAnnotPropTable, inst_tbl, &key, &ret);

    CowlAnnotProp *prop;

    if (ret == UHASH_INSERTED) {
        prop = cowl_annot_prop_alloc(iri);
        uhash_key(inst_tbl, idx) = prop;
    } else {
        prop = uhash_key(inst_tbl, idx);
        cowl_object_retain(prop);
    }

    return prop;
}

CowlAnnotProp* cowl_annot_prop_retain(CowlAnnotProp *prop) {
    return cowl_object_retain(prop);
}

void cowl_annot_prop_release(CowlAnnotProp *prop) {
    if (prop && !cowl_object_release(prop)) {
        uhset_remove(CowlAnnotPropTable, inst_tbl, prop);
        cowl_annot_prop_free(prop);
    }
}

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return prop->iri;
}

CowlString* cowl_annot_prop_to_string(CowlAnnotProp *prop) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_annot_prop(buf, prop);
    return cowl_str_buf_to_string(buf);
}

bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_annot_prop_hash(CowlAnnotProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_annot_prop_iterate_signature(CowlAnnotProp *prop, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_annot_prop(prop));
}
