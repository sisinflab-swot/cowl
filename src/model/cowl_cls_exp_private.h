/// @author Ivano Bilenchi

#ifndef COWL_CLS_EXP_PRIVATE_H
#define COWL_CLS_EXP_PRIVATE_H

#include "cowl_cls_exp.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp {
    CowlObject super;
    CowlClsExpType type;
} CowlClsExp;

#define COWL_CLS_EXP_INIT(T, H) { .super = COWL_OBJECT_INIT(H), .type = (T) }

#define cowl_cls_exp_ref_get(c) cowl_object_ref_get(c)
#define cowl_cls_exp_ref_incr(c) cowl_object_retain(c)
#define cowl_cls_exp_ref_decr(c) cowl_object_release(c)

#define cowl_cls_exp_hash_get(c) cowl_object_hash_get(c)
#define cowl_cls_exp_hash_set(c, h) cowl_object_hash_set(c, h)

COWL_END_DECLS

#endif // COWL_CLS_EXP_PRIVATE_H
