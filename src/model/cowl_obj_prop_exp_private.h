/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_PRIVATE_H
#define COWL_OBJ_PROP_EXP_PRIVATE_H

#include "cowl_obj_prop_exp.h"

COWL_BEGIN_DECLS

cowl_struct(CowlObjPropExp) {
    bool is_inverse;
    cowl_uint_t ref_count;
};

#define COWL_OBJ_PROP_EXP_INIT(I) { .ref_count = 1, .is_inverse = ((I)) }

#define cowl_obj_prop_exp_ref_get(o) (((cowl_struct(CowlObjPropExp) *)(o))->ref_count)
#define cowl_obj_prop_exp_ref_incr(o) (++cowl_obj_prop_exp_ref_get(o), (o))
#define cowl_obj_prop_exp_ref_decr(o) (--cowl_obj_prop_exp_ref_get(o))

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_PRIVATE_H
