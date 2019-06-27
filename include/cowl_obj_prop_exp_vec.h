/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_EXP_VEC_H
#define COWL_OBJ_PROP_EXP_VEC_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);
typedef CowlObjPropExp* CowlObjPropExpPtr;

VECTOR_DECL_EQUATABLE(CowlObjPropExpPtr)
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);

void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec);

bool cowl_obj_prop_exp_vec_equals(CowlObjPropExpVec *lhs, CowlObjPropExpVec *rhs);
cowl_uint_t cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec);

bool cowl_obj_prop_exp_vec_iterate_signature(CowlObjPropExpVec *vec, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_VEC_H
