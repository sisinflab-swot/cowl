/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_H
#define COWL_CLS_EXP_H

#include "cowl_cls_exp_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlClsExp CowlClsExp;
KHASH_SET_UTILS_DECL(CowlClsExpSet, CowlClsExp const*);

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp const *exp);

bool cowl_cls_exp_enum_signature(CowlClsExp const *exp, void *ctx, CowlEntityIterator iter);

bool cowl_cls_exp_equals(CowlClsExp const *lhs, CowlClsExp const *rhs);
uint32_t cowl_cls_exp_hash(CowlClsExp const *exp);

COWL_END_DECLS

#endif // COWL_CLS_EXP_H
