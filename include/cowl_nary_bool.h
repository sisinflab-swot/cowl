/// @author Ivano Bilenchi

#ifndef COWL_NARY_BOOL_H
#define COWL_NARY_BOOL_H

#include "cowl_iterator.h"
#include "cowl_nary_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlClsExpSet);

cowl_struct_decl(CowlNAryBool);

CowlNAryBool* cowl_nary_bool_get(CowlNAryType type, CowlClsExpSet *operands);
CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp);
void cowl_nary_bool_release(CowlNAryBool *exp);

CowlNAryType cowl_nary_bool_get_type(CowlNAryBool *exp);
CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp);

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs);
cowl_uint_t cowl_nary_bool_hash(CowlNAryBool *exp);

bool cowl_nary_bool_iterate_signature(CowlNAryBool *exp, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_BOOL_H
