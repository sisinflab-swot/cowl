/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop_private.h"
#include "cowl_iri.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlAnnotPropTable, CowlAnnotProp*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlAnnotPropTable) *inst_tbl = NULL;

cowl_ret_t cowl_annot_prop_api_init(void) {
    inst_tbl = uhset_alloc(CowlAnnotPropTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_annot_prop_api_deinit(void) {
    uhash_free(CowlAnnotPropTable, inst_tbl);
}

static CowlAnnotProp* cowl_annot_prop_alloc(CowlIRI *iri) {
    CowlAnnotProp *prop = cowl_alloc(prop);
    if (!prop) return NULL;

    *prop = (CowlAnnotProp) {
        .super = COWL_OBJECT_INIT(COWL_OT_ANNOT_PROP),
        .iri = cowl_iri_retain(iri)
    };

    return prop;
}

static void cowl_annot_prop_free(CowlAnnotProp *prop) {
    if (!prop) return;
    cowl_iri_release(prop->iri);
    cowl_free(prop);
}

CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(AnnotProp, annot_prop, { .iri = iri }, cowl_annot_prop_alloc(iri))
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

CowlAnnotProp* cowl_annot_prop_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(AnnotProp, annot_prop)

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return prop->iri;
}

CowlString* cowl_annot_prop_to_string(CowlAnnotProp *prop)
    COWL_TO_STRING_IMPL(annot_prop, prop)

bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_annot_prop_hash(CowlAnnotProp *prop) {
    return uhash_ptr_hash(prop);
}

bool cowl_annot_prop_iterate_primitives(CowlAnnotProp *prop, CowlIterator *iter,
                                        CowlPrimitiveFlags flags) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP) ? cowl_iterate(iter, prop) : true;
}
