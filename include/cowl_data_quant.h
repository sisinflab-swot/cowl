/// @author Ivano Bilenchi

#ifndef COWL_DATA_QUANT_H
#define COWL_DATA_QUANT_H

#include "cowl_std.h"
#include "cowl_iterator.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);

cowl_struct_decl(CowlDataQuant);

CowlDataQuant* cowl_data_quant_get(CowlQuantType type, CowlDataPropExp *prop,
                                   CowlDataRange *range);
CowlDataQuant* cowl_data_quant_retain(CowlDataQuant *restr);
void cowl_data_quant_release(CowlDataQuant *restr);

CowlQuantType cowl_data_quant_get_type(CowlDataQuant *restr);
CowlDataPropExp* cowl_data_quant_get_prop(CowlDataQuant *restr);
CowlDataRange* cowl_data_quant_get_range(CowlDataQuant *restr);

bool cowl_data_quant_equals(CowlDataQuant *lhs, CowlDataQuant *rhs);
cowl_uint_t cowl_data_quant_hash(CowlDataQuant *restr);

bool cowl_data_quant_iterate_signature(CowlDataQuant *restr, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_QUANT_H
