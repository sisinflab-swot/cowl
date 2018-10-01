/// @author Ivano Bilenchi

#ifndef COWL_SUB_CLS_AXIOM_H
#define COWL_SUB_CLS_AXIOM_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;

typedef struct CowlSubClsAxiom CowlSubClsAxiom;

CowlClsExp const* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom const *axiom);
CowlClsExp const* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom const *axiom);

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom const *lhs, CowlSubClsAxiom const *rhs);
uint32_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
