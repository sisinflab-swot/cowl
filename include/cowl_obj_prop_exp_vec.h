/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_VEC_H
#define COWL_OBJ_PROP_EXP_VEC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);
typedef CowlObjPropExp* CowlObjPropExpPtr;

VECTOR_DECL_EQUATABLE(CowlObjPropExpPtr)
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);

cowl_uint_t cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec);
void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_VEC_H
