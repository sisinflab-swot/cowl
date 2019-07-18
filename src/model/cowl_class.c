/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_class_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlClassTable, CowlClass*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlClassTable) *inst_tbl = NULL;

static CowlClass* cowl_class_alloc(CowlIRI *iri) {
    CowlClass init = {
        .super = COWL_CLS_EXP_INIT(COWL_CET_CLASS, 0),
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
    if (!inst_tbl) inst_tbl = uhset_alloc(CowlClassTable);

    uhash_ret_t ret;
    CowlClass key = { .iri = iri };
    uhash_uint_t idx = uhash_put(CowlClassTable, inst_tbl, &key, &ret);

    CowlClass *cls;

    if (ret == UHASH_INSERTED) {
        cls = cowl_class_alloc(iri);
        uhash_key(inst_tbl, idx) = cls;
    } else {
        cls = uhash_key(inst_tbl, idx);
        cowl_object_retain(cls);
    }

    return cls;
}

CowlClass* cowl_class_retain(CowlClass *cls) {
    return cowl_object_retain(cls);
}

void cowl_class_release(CowlClass *cls) {
    if (cls && !cowl_object_release(cls)) {
        uhset_remove(CowlClassTable, inst_tbl, cls);
        cowl_class_free(cls);
    }
}

CowlIRI* cowl_class_get_iri(CowlClass *cls) {
    return cls->iri;
}

CowlString* cowl_class_to_string(CowlClass *cls) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_class(buf, cls);
    return cowl_str_buf_to_string(buf);
}

bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_class_hash(CowlClass *cls) {
    return cowl_object_hash_get(cls);
}

bool cowl_class_iterate_signature(CowlClass *cls, CowlEntityIterator *iter) {
    return cowl_iterate(iter, cowl_entity_wrap_class(cls));
}
