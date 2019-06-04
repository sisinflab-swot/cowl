/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_VEC_PRIVATE_H
#define COWL_OBJ_PROP_EXP_VEC_PRIVATE_H

#include "cowl_obj_prop_exp_vec.h"

COWL_BEGIN_DECLS

cowl_vector_decl_mutable(CowlObjPropExpPtr, CowlMutableObjPropExpVec);

void cowl_obj_prop_exp_vec_push(CowlMutableObjPropExpVec *vec, CowlObjPropExp *exp);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_VEC_PRIVATE_H
