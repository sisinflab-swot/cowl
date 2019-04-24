/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_SET_H
#define COWL_CLS_EXP_SET_H

#include "cowl_std.h"
#include "uhash.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;

UHASH_SET_DECL(CowlClsExpSet, CowlClsExp*);
typedef struct UHash(CowlClsExpSet) const CowlClsExpSet;
typedef struct UHash(CowlClsExpSet) CowlMutableClsExpSet;

bool cowl_cls_exp_set_insert(CowlMutableClsExpSet *set, CowlClsExp *exp);
void cowl_cls_exp_set_free(CowlClsExpSet *set);

COWL_END_DECLS

#endif // COWL_CLS_EXP_SET_H
