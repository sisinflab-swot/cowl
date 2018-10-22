/// @author Ivano Bilenchi

#ifndef COWL_DISJ_CLS_AXIOM_H
#define COWL_DISJ_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) const CowlClsExpSet;

typedef struct CowlDisjClsAxiom const CowlDisjClsAxiom;

CowlDisjClsAxiom* cowl_disj_cls_axiom_get(CowlClsExpSet *classes);
CowlDisjClsAxiom* cowl_disj_cls_axiom_retain(CowlDisjClsAxiom *axiom);
void cowl_disj_cls_axiom_release(CowlDisjClsAxiom *axiom);

CowlClsExpSet* cowl_disj_cls_axiom_get_classes(CowlDisjClsAxiom *axiom);

bool cowl_disj_cls_axiom_equals(CowlDisjClsAxiom *lhs, CowlDisjClsAxiom *rhs);
uint32_t cowl_disj_cls_axiom_hash(CowlDisjClsAxiom *axiom);

bool cowl_disj_cls_axiom_iterate_signature(CowlDisjClsAxiom *axiom,
                                           void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DISJ_CLS_AXIOM_H
