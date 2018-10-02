/// @author Ivano Bilenchi

#ifndef COWL_DECL_AXIOM_H
#define COWL_DECL_AXIOM_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity CowlEntity;

typedef struct CowlDeclAxiom CowlDeclAxiom;

CowlEntity const* cowl_decl_axiom_get_entity(CowlDeclAxiom const *axiom);

bool cowl_decl_axiom_equals(CowlDeclAxiom const *lhs, CowlDeclAxiom const *rhs);
uint32_t cowl_decl_axiom_hash(CowlDeclAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H
