/// @author Ivano Bilenchi

#ifndef COWL_SUB_CLS_AXIOM_H
#define COWL_SUB_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;

typedef struct CowlSubClsAxiom CowlSubClsAxiom;

CowlSubClsAxiom const* cowl_sub_cls_axiom_get(CowlClsExp const *super, CowlClsExp const *sub);
CowlSubClsAxiom const* cowl_sub_cls_axiom_retain(CowlSubClsAxiom const *axiom);
void cowl_sub_cls_axiom_release(CowlSubClsAxiom const *axiom);

CowlClsExp const* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom const *axiom);
CowlClsExp const* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom const *axiom);

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom const *lhs, CowlSubClsAxiom const *rhs);
uint32_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom const *axiom);

bool cowl_sub_cls_axiom_iterate_signature(CowlSubClsAxiom const *axiom,
                                          void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
