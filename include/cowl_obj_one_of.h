/// @author Ivano Bilenchi

#ifndef COWL_OBJ_ONE_OF_H
#define COWL_OBJ_ONE_OF_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlIndividualSet);

cowl_struct_decl(CowlObjOneOf);

CowlObjOneOf* cowl_obj_one_of_get(CowlIndividualSet *inds);
CowlObjOneOf* cowl_obj_one_of_retain(CowlObjOneOf *exp);
void cowl_obj_one_of_release(CowlObjOneOf *exp);

CowlIndividualSet* cowl_obj_one_of_get_inds(CowlObjOneOf *exp);

bool cowl_obj_one_of_equals(CowlObjOneOf *lhs, CowlObjOneOf *rhs);
cowl_uint_t cowl_obj_one_of_hash(CowlObjOneOf *exp);

bool cowl_obj_one_of_iterate_signature(CowlObjOneOf *exp, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_ONE_OF_H
