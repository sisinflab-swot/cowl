/// @author Ivano Bilenchi

#include "cowl_decl_axiom_private.h"
#include "cowl_entity.h"
#include "cowl_hash_utils.h"

CowlEntity const* cowl_decl_axiom_get_entity(CowlDeclAxiom const *axiom) {
    return axiom->entity;
}

bool cowl_decl_axiom_equals(CowlDeclAxiom const *lhs, CowlDeclAxiom const *rhs) {
    return cowl_entity_equals(lhs->entity, rhs->entity);
}

uint32_t cowl_decl_axiom_hash(CowlDeclAxiom const *axiom) {
    return cowl_hash_1(COWL_HASH_INIT_DECL_AXIOM, cowl_entity_hash(axiom->entity));
}
