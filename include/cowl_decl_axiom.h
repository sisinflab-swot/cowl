/// @author Ivano Bilenchi

#ifndef COWL_DECL_AXIOM_H
#define COWL_DECL_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlDeclAxiom CowlDeclAxiom;

CowlDeclAxiom const* cowl_decl_axiom_get(CowlEntity entity);
CowlDeclAxiom const* cowl_decl_axiom_retain(CowlDeclAxiom const *axiom);
void cowl_decl_axiom_release(CowlDeclAxiom const *axiom);

CowlEntity cowl_decl_axiom_get_entity(CowlDeclAxiom const *axiom);

bool cowl_decl_axiom_equals(CowlDeclAxiom const *lhs, CowlDeclAxiom const *rhs);
uint32_t cowl_decl_axiom_hash(CowlDeclAxiom const *axiom);

bool cowl_decl_axiom_iterate_signature(CowlDeclAxiom const *axiom,
                                       void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DECL_AXIOM_H