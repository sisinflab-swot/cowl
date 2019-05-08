/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_SET_PRIVATE_H
#define COWL_CLS_EXP_SET_PRIVATE_H

#include "cowl_cls_exp_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlClsExpSet, CowlMutableClsExpSet);

bool cowl_cls_exp_set_insert(CowlMutableClsExpSet *set, CowlClsExp *exp);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_PRIVATE_H
