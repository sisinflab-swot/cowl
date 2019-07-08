/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_named_ind_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"

UHASH_MAP_INIT(CowlNamedIndMap, CowlIRI*, CowlNamedInd*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlNamedIndMap) *inst_map = NULL;

static CowlNamedInd* cowl_named_ind_alloc(CowlIRI *iri) {
    CowlNamedInd ind_init = {
        .super = COWL_INDIVIDUAL_INIT(true),
        .iri = cowl_iri_retain(iri)
    };
    cowl_struct(CowlNamedInd) *ind = malloc(sizeof(*ind));
    memcpy(ind, &ind_init, sizeof(*ind));
    return ind;
}

static void cowl_named_ind_free(CowlNamedInd *ind) {
    if (!ind) return;
    cowl_iri_release(ind->iri);
    free((void *)ind);
}

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlNamedIndMap);

    CowlNamedInd *ind;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlNamedIndMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        ind = cowl_named_ind_alloc(iri);
        uhash_value(inst_map, idx) = ind;
    } else {
        ind = uhash_value(inst_map, idx);
        cowl_object_retain(ind);
    }

    return ind;
}

CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind) {
    return cowl_object_retain(ind);
}

void cowl_named_ind_release(CowlNamedInd *ind) {
    if (ind && !cowl_object_release(ind)) {
        uhmap_remove(CowlNamedIndMap, inst_map, ind->iri);
        cowl_named_ind_free(ind);
    }
}

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind) {
    return ind->iri;
}

bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_named_ind_hash(CowlNamedInd *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_named_ind_iterate_signature(CowlNamedInd *ind, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_named_ind(ind));
}
