/// @author Ivano Bilenchi

#ifndef COWL_DATA_HAS_VALUE_H
#define COWL_DATA_HAS_VALUE_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlLiteral);

cowl_struct_decl(CowlDataHasValue);

CowlDataHasValue* cowl_data_has_value_get(CowlDataPropExp *prop, CowlLiteral *value);
CowlDataHasValue* cowl_data_has_value_retain(CowlDataHasValue *exp);
void cowl_data_has_value_release(CowlDataHasValue *exp);

CowlDataPropExp* cowl_data_has_value_get_prop(CowlDataHasValue *exp);
CowlLiteral* cowl_data_has_value_get_value(CowlDataHasValue *exp);

bool cowl_data_has_value_equals(CowlDataHasValue *lhs, CowlDataHasValue *rhs);
cowl_uint_t cowl_data_has_value_hash(CowlDataHasValue *exp);

bool cowl_data_has_value_iterate_signature(CowlDataHasValue *exp, void *ctx,
                                           CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_HAS_VALUE_H
