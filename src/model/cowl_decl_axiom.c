/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_decl_axiom_private.h"
#include "cowl_iterator_private.h"
#include "cowl_str_buf.h"

static CowlDeclAxiom* cowl_decl_axiom_alloc(CowlEntity entity, CowlAnnotationVec *annot) {
    cowl_uint_t hash = cowl_axiom_hash_1(COWL_HASH_INIT_DECL_AXIOM, annot,
                                         cowl_entity_hash(entity));

    CowlDeclAxiom init = {
        .super = COWL_AXIOM_INIT(COWL_AT_DECL, hash, annot),
        .entity = cowl_entity_retain(entity)
    };

    cowl_struct(CowlDeclAxiom) *axiom;
    cowl_axiom_alloc(axiom, init, annot);
    return axiom;
}

static void cowl_decl_axiom_free(CowlDeclAxiom *axiom) {
    if (!axiom) return;
    cowl_entity_release(axiom->entity);
    cowl_axiom_free(axiom);
}

CowlDeclAxiom* cowl_decl_axiom_get(CowlEntity entity, CowlAnnotationVec *annot) {
    return cowl_decl_axiom_alloc(entity, annot);
}

CowlDeclAxiom* cowl_decl_axiom_retain(CowlDeclAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_decl_axiom_release(CowlDeclAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_decl_axiom_free(axiom);
    }
}

CowlEntity cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom) {
    return axiom->entity;
}

CowlAnnotationVec* cowl_decl_axiom_get_annot(CowlDeclAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_decl_axiom_to_string(CowlDeclAxiom *axiom) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_decl_axiom(buf, axiom);
    return cowl_str_buf_to_string(buf);
}

bool cowl_decl_axiom_equals(CowlDeclAxiom *lhs, CowlDeclAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_entity_equals(lhs->entity, rhs->entity));
}

cowl_uint_t cowl_decl_axiom_hash(CowlDeclAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_decl_axiom_iterate_signature(CowlDeclAxiom *axiom, CowlEntityIterator *iter) {
    if (!cowl_iterate(iter, axiom->entity)) return false;
    if (!cowl_axiom_annot_iterate_signature(axiom, iter)) return false;
    return true;
}
