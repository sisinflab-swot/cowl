/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_RANGE_AXIOM_H
#define COWL_DATA_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);

cowl_struct_decl(CowlDataPropRangeAxiom);

CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_get(CowlDataPropExp *prop, CowlDataRange *range);
CowlDataPropRangeAxiom* cowl_data_prop_range_axiom_retain(CowlDataPropRangeAxiom *axiom);
void cowl_data_prop_range_axiom_release(CowlDataPropRangeAxiom *axiom);

CowlDataPropExp* cowl_data_prop_range_axiom_get_prop(CowlDataPropRangeAxiom *axiom);
CowlDataRange* cowl_data_prop_range_axiom_get_range(CowlDataPropRangeAxiom *axiom);

bool cowl_data_prop_range_axiom_equals(CowlDataPropRangeAxiom *lhs, CowlDataPropRangeAxiom *rhs);
cowl_uint_t cowl_data_prop_range_axiom_hash(CowlDataPropRangeAxiom *axiom);

bool cowl_data_prop_range_axiom_iterate_signature(CowlDataPropRangeAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_RANGE_AXIOM_H
