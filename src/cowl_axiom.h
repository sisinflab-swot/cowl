/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_H
#define COWL_AXIOM_H

#include "cowl_std.h"
#include "cowl_axiom_type.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom CowlAxiom;

CowlAxiomType cowl_axiom_get_type(CowlAxiom const *axiom);

bool cowl_axiom_equals(CowlAxiom const *lhs, CowlAxiom const *rhs);
uint32_t cowl_axiom_hash(CowlAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_AXIOM_H
