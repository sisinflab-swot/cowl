/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_object_table.h"
#include "cowl_template.h"

static UHash(CowlObjectTable) *inst_tbl = NULL;

static ulib_uint inst_tbl_hash(void *key) {
    return cowl_iri_hash(cowl_annot_prop_get_iri(key));
}

static bool inst_tbl_eq(void *lhs, void *rhs) {
    return cowl_iri_equals(cowl_annot_prop_get_iri(lhs), cowl_annot_prop_get_iri(rhs));
}

cowl_ret cowl_annot_prop_api_init(void) {
    inst_tbl = uhset_alloc_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_annot_prop_api_deinit(void) {
    uhash_free(CowlObjectTable, inst_tbl);
}

static CowlAnnotProp* cowl_annot_prop_alloc(CowlIRI *iri) {
    CowlAnnotProp *prop = ulib_alloc(prop);
    if (!prop) return NULL;

    *prop = (CowlAnnotProp) {
        .super = COWL_OBJECT_INIT(COWL_OT_ANNOT_PROP),
        .iri = cowl_iri_retain(iri)
    };

    return prop;
}

static void cowl_annot_prop_free(CowlAnnotProp *prop) {
    cowl_iri_release(prop->iri);
    ulib_free(prop);
}

CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(AnnotProp, annot_prop, { .iri = iri }, cowl_annot_prop_alloc(iri))
}

CowlAnnotProp* cowl_annot_prop_retain(CowlAnnotProp *prop) {
    return cowl_object_incr_ref(prop);
}

void cowl_annot_prop_release(CowlAnnotProp *prop) {
    if (prop && !cowl_object_decr_ref(prop)) {
        uhset_remove(CowlObjectTable, inst_tbl, prop);
        cowl_annot_prop_free(prop);
    }
}

CowlAnnotProp* cowl_annot_prop_from_string(UString string)
    COWL_ENTITY_FROM_STRING_IMPL(AnnotProp, annot_prop)

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return prop->iri;
}

CowlString* cowl_annot_prop_to_string(CowlAnnotProp *prop)
    COWL_TO_STRING_IMPL(annot_prop, prop)

bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs) {
    return lhs == rhs;
}

ulib_uint cowl_annot_prop_hash(CowlAnnotProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_annot_prop_iterate_primitives(CowlAnnotProp *prop, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP) ? cowl_iterate(iter, prop) : true;
}
