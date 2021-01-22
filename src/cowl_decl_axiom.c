/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_decl_axiom_private.h"
#include "cowl_entity.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDeclAxiom* cowl_decl_axiom_alloc(CowlEntity *entity, CowlAnnotationVec *annot) {
    CowlDeclAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_1(COWL_HASH_INIT_DECL_AXIOM, annot,
                                       cowl_entity_hash(entity));

    cowl_axiom_init(CowlDeclAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DECL, hash, annot),
        .entity = cowl_entity_retain(entity)
    );

    return axiom;
}

static void cowl_decl_axiom_free(CowlDeclAxiom *axiom) {
    if (!axiom) return;
    cowl_entity_release(axiom->entity);
    cowl_axiom_free(axiom);
}

CowlDeclAxiom* cowl_decl_axiom_get(CowlEntity *entity, CowlAnnotationVec *annot) {
    return cowl_decl_axiom_alloc(entity, annot);
}

CowlDeclAxiom* cowl_decl_axiom_retain(CowlDeclAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_decl_axiom_release(CowlDeclAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_decl_axiom_free(axiom);
    }
}

CowlEntity* cowl_decl_axiom_get_entity(CowlDeclAxiom *axiom) {
    return axiom->entity;
}

CowlAnnotationVec* cowl_decl_axiom_get_annot(CowlDeclAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_decl_axiom_to_string(CowlDeclAxiom *axiom)
    COWL_TO_STRING_IMPL(decl_axiom, axiom)

bool cowl_decl_axiom_equals(CowlDeclAxiom *lhs, CowlDeclAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs, cowl_entity_equals(lhs->entity, rhs->entity));
}

cowl_uint cowl_decl_axiom_hash(CowlDeclAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_decl_axiom_iterate_primitives(CowlDeclAxiom *axiom, CowlIterator *iter,
                                        CowlPrimitiveFlags flags) {
    return (cowl_entity_iterate_primitives(axiom->entity, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
