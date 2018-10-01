/// @author Ivano Bilenchi

#ifndef COWL_OBJ_UNION_H
#define COWL_OBJ_UNION_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef khash_struct(CowlClsExpSet) khash_t(CowlClsExpSet);

typedef struct CowlObjUnion CowlObjUnion;

khash_t(CowlClsExpSet) const* cowl_obj_union_get_operands(CowlObjUnion const *exp);

bool cowl_obj_union_equals(CowlObjUnion const *lhs, CowlObjUnion const *rhs);
uint32_t cowl_obj_union_hash(CowlObjUnion const *exp);

COWL_END_DECLS

#endif // COWL_OBJ_UNION_H
