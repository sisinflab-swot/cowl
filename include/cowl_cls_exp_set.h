/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_SET_H
#define COWL_CLS_EXP_SET_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;

KHASH_SET_UTILS_DECL(CowlClsExpSet, CowlClsExp*);
typedef khash_struct(CowlClsExpSet) const CowlClsExpSet;
typedef khash_struct(CowlClsExpSet) CowlMutableClsExpSet;

bool cowl_cls_exp_set_insert(CowlMutableClsExpSet *set, CowlClsExp *exp);
void cowl_cls_exp_set_free(CowlClsExpSet *set);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_H
