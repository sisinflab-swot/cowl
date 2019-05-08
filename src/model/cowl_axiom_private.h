/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_PRIVATE_H
#define COWL_AXIOM_PRIVATE_H

#include "cowl_axiom.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAxiom) {
    CowlObject super;
    CowlAxiomType type;
};

#define COWL_AXIOM_INIT(T, H) { .super = COWL_OBJECT_INIT(H), .type = (T) }

#define cowl_axiom_ref_get(a) cowl_object_ref_get(a)
#define cowl_axiom_ref_incr(a) cowl_object_retain(a)
#define cowl_axiom_ref_decr(a) cowl_object_release(a)

#define cowl_axiom_hash_get(a) cowl_object_hash_get(a)
#define cowl_axiom_hash_set(a, h) cowl_object_hash_set(a, h)

COWL_END_DECLS

#endif // COWL_AXIOM_PRIVATE_H
