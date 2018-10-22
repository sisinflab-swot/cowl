/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_SET_H
#define COWL_AXIOM_SET_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom CowlAxiom;

KHASH_SET_UTILS_DECL(CowlAxiomSet, CowlAxiom const*);

bool cowl_axiom_set_add(khash_t(CowlAxiomSet) *set, CowlAxiom const *axiom);
void cowl_axiom_set_free(khash_t(CowlAxiomSet) const *set);

COWL_END_DECLS

#endif // COWL_AXIOM_SET_H
