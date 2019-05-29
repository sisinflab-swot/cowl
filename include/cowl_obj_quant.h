/// @author Ivano Bilenchi

#ifndef COWL_OBJ_QUANT_H
#define COWL_OBJ_QUANT_H

#include "cowl_std.h"
#include "cowl_iterator.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlObjQuant);

CowlObjQuant* cowl_obj_quant_get(CowlQuantType type, CowlObjPropExp *prop, CowlClsExp *filler);
CowlObjQuant* cowl_obj_quant_retain(CowlObjQuant *restr);
void cowl_obj_quant_release(CowlObjQuant *restr);

CowlQuantType cowl_obj_quant_get_type(CowlObjQuant *restr);
CowlObjPropExp* cowl_obj_quant_get_prop(CowlObjQuant *restr);
CowlClsExp* cowl_obj_quant_get_filler(CowlObjQuant *restr);

bool cowl_obj_quant_equals(CowlObjQuant *lhs, CowlObjQuant *rhs);
cowl_uint_t cowl_obj_quant_hash(CowlObjQuant *restr);

bool cowl_obj_quant_iterate_signature(CowlObjQuant *restr, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_QUANT_H
