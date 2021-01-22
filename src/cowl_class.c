/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_class_private.h"
#include "cowl_iri_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

#define cowl_inst_hash(X) cowl_iri_hash((X)->iri)
#define cowl_inst_eq(A, B) cowl_iri_equals((A)->iri, (B)->iri)

UHASH_INIT(CowlClassTable, CowlClass*, UHASH_VAL_IGNORE, cowl_inst_hash, cowl_inst_eq)
static UHash(CowlClassTable) *inst_tbl = NULL;

cowl_ret cowl_class_api_init(void) {
    inst_tbl = uhset_alloc(CowlClassTable);
    return inst_tbl ? COWL_OK : COWL_ERR_MEM;
}

void cowl_class_api_deinit(void) {
    uhash_free(CowlClassTable, inst_tbl);
}

static CowlClass* cowl_class_alloc(CowlIRI *iri) {
    CowlClass *cls = cowl_alloc(cls);
    if (!cls) return NULL;

    (*cls) = (CowlClass) {
        .super = COWL_CLS_EXP_INIT(COWL_CET_CLASS, 0),
        .iri = cowl_iri_retain(iri)
    };

    cowl_uint hash = uhash_ptr_hash(cls);
    cowl_object_hash_set(cls, hash);

    return cls;
}

static void cowl_class_free(CowlClass *cls) {
    if (!cls) return;
    cowl_iri_release(cls->iri);
    cowl_free(cls);
}

CowlClass* cowl_class_get(CowlIRI *iri) {
    if (!iri) return NULL;
    COWL_INST_TBL_GET_IMPL(Class, class, { .iri = iri }, cowl_class_alloc(iri))
}

CowlClass* cowl_class_retain(CowlClass *cls) {
    return cowl_object_incr_ref(cls);
}

void cowl_class_release(CowlClass *cls) {
    if (cls && !cowl_object_decr_ref(cls)) {
        uhset_remove(CowlClassTable, inst_tbl, cls);
        cowl_class_free(cls);
    }
}

CowlClass* cowl_class_from_cstring(char const *cstring, size_t length)
    COWL_ENTITY_FROM_CSTRING_IMPL(Class, class)

CowlIRI* cowl_class_get_iri(CowlClass *cls) {
    return cls->iri;
}

CowlString* cowl_class_to_string(CowlClass *cls)
    COWL_TO_STRING_IMPL(class, cls)

bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs) {
    return lhs == rhs;
}

cowl_uint cowl_class_hash(CowlClass *cls) {
    return cowl_object_hash_get(cls);
}

bool cowl_class_iterate_primitives(CowlClass *cls, CowlIterator *iter, CowlPrimitiveFlags flags) {
    return uflags_is_set(COWL_PF, flags, COWL_PF_CLASS) ? cowl_iterate(iter, cls) : true;
}
