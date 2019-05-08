/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_SET_H
#define COWL_CLS_EXP_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);

UHASH_SET_DECL(CowlClsExpSet, CowlClsExp*)
cowl_hash_decl(CowlClsExpSet);

void cowl_cls_exp_set_free(CowlClsExpSet *set);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_H
