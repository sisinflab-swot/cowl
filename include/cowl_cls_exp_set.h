/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_SET_H
#define COWL_CLS_EXP_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);

UHASH_SET_DECL(CowlClsExpSet, CowlClsExp*)
cowl_hash_decl(CowlClsExpSet);

void cowl_cls_exp_set_free(CowlClsExpSet *set);

bool cowl_cls_exp_set_equals(CowlClsExpSet *lhs, CowlClsExpSet *rhs);
cowl_uint_t cowl_cls_exp_set_hash(CowlClsExpSet *set);

bool cowl_cls_exp_set_iterate_signature(CowlClsExpSet *set, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_H
