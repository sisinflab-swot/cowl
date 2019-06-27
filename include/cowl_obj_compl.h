/// @author Ivano Bilenchi

#ifndef COWL_OBJ_COMPL_H
#define COWL_OBJ_COMPL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);

cowl_struct_decl(CowlObjCompl);

CowlObjCompl* cowl_obj_compl_get(CowlClsExp *operand);
CowlObjCompl* cowl_obj_compl_retain(CowlObjCompl *exp);
void cowl_obj_compl_release(CowlObjCompl *exp);

CowlClsExp* cowl_obj_compl_get_operand(CowlObjCompl *exp);

bool cowl_obj_compl_equals(CowlObjCompl *lhs, CowlObjCompl *rhs);
cowl_uint_t cowl_obj_compl_hash(CowlObjCompl *exp);

bool cowl_obj_compl_iterate_signature(CowlObjCompl *exp, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_H
