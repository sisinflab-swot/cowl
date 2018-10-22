/// @author Ivano Bilenchi

#include "cowl_decl_axiom_private.h"
#include "cowl_hash_utils.h"

#pragma mark - Private

static CowlDeclAxiom* cowl_decl_axiom_alloc(CowlEntity entity) {
    uint32_t hash = cowl_hash_1(COWL_HASH_INIT_DECL_AXIOM, cowl_entity_hash(entity));

    CowlDeclAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DECLARATION, hash),
        .entity = cowl_entity_retain(entity)
    };

    CowlDeclAxiom *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_decl_axiom_free(CowlDeclAxiom const *axiom) {
    if (!axiom) return;
    cowl_entity_release(axiom->entity);
    free((void *)axiom);
}

#pragma mark - Public

CowlDeclAxiom const* cowl_decl_axiom_get(CowlEntity entity) {
    return cowl_decl_axiom_alloc(entity);
}

CowlDeclAxiom const* cowl_decl_axiom_retain(CowlDeclAxiom const *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_decl_axiom_release(CowlDeclAxiom const *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_decl_axiom_free(axiom);
    }
}

CowlEntity cowl_decl_axiom_get_entity(CowlDeclAxiom const *axiom) {
    return axiom->entity;
}

bool cowl_decl_axiom_equals(CowlDeclAxiom const *lhs, CowlDeclAxiom const *rhs) {
    return cowl_entity_equals(lhs->entity, rhs->entity);
}

uint32_t cowl_decl_axiom_hash(CowlDeclAxiom const *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_decl_axiom_iterate_signature(CowlDeclAxiom const *axiom,
                                       void *ctx, CowlEntityIterator iter) {
    return iter(ctx, axiom->entity);
}
