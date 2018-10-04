/// @author Ivano Bilenchi

#ifndef COWL_DECL_AXIOM_PRIVATE_H
#define COWL_DECL_AXIOM_PRIVATE_H

#include "cowl_decl_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

typedef struct CowlDeclAxiom {
    CowlAxiom super;
    CowlEntity entity;
} CowlDeclAxiom;

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_PRIVATE_H
