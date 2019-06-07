/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_PRIVATE_H
#define COWL_AXIOM_PRIVATE_H

#include "cowl_axiom.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAxiom) {
    CowlHashObject super;
    CowlAxiomType type;
};

#define COWL_AXIOM_INIT(T, H) { .super = COWL_HASH_OBJECT_INIT(H), .type = (T) }

COWL_END_DECLS

#endif // COWL_AXIOM_PRIVATE_H
