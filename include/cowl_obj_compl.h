/// @author Ivano Bilenchi

#ifndef COWL_OBJ_COMPL_H
#define COWL_OBJ_COMPL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;

typedef struct CowlObjCompl CowlObjCompl;

CowlObjCompl const* cowl_obj_compl_get(CowlClsExp const *operand);
CowlObjCompl const* cowl_obj_compl_retain(CowlObjCompl const *compl);
void cowl_obj_compl_release(CowlObjCompl const *compl);

CowlClsExp const* cowl_obj_compl_get_operand(CowlObjCompl const *compl);

bool cowl_obj_compl_equals(CowlObjCompl const *lhs, CowlObjCompl const *rhs);
uint32_t cowl_obj_compl_hash(CowlObjCompl const *compl);

bool cowl_obj_compl_iterate_signature(CowlObjCompl const *compl,
                                      void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_COMPL_H
