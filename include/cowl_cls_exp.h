/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_H
#define COWL_CLS_EXP_H

#include "cowl_cls_exp_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlClsExp const CowlClsExp;

CowlClsExp* cowl_cls_exp_retain(CowlClsExp *exp);
void cowl_cls_exp_release(CowlClsExp *exp);

CowlClsExpType cowl_cls_exp_get_type(CowlClsExp *exp);

bool cowl_cls_exp_equals(CowlClsExp *lhs, CowlClsExp *rhs);
cowl_uint_t cowl_cls_exp_hash(CowlClsExp *exp);

bool cowl_cls_exp_iterate_signature(CowlClsExp *exp, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_CLS_EXP_H
