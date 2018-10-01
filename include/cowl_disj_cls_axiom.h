/// @author Ivano Bilenchi

#ifndef COWL_DISJ_CLS_AXIOM_H
#define COWL_DISJ_CLS_AXIOM_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) khash_t(CowlClsExpSet);

typedef struct CowlDisjClsAxiom CowlDisjClsAxiom;

khash_t(CowlClsExpSet) const *cowl_disj_cls_axiom_get_classes(CowlDisjClsAxiom const *axiom);

bool cowl_disj_cls_axiom_equals(CowlDisjClsAxiom const *lhs, CowlDisjClsAxiom const *rhs);
uint32_t cowl_disj_cls_axiom_hash(CowlDisjClsAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_DISJ_CLS_AXIOM_H
