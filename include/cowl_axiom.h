/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_H
#define COWL_AXIOM_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom CowlAxiom;

CowlAxiom const* cowl_axiom_retain(CowlAxiom const *axiom);
void cowl_axiom_release(CowlAxiom const *axiom);

CowlAxiomType cowl_axiom_get_type(CowlAxiom const *axiom);

bool cowl_axiom_equals(CowlAxiom const *lhs, CowlAxiom const *rhs);
uint32_t cowl_axiom_hash(CowlAxiom const *axiom);

bool cowl_axiom_iterate_signature(CowlAxiom const *axiom, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_AXIOM_H
