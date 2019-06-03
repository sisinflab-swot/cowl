/// @author Ivano Bilenchi

#ifndef COWL_FUNC_DATA_PROP_AXIOM_H
#define COWL_FUNC_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);

cowl_struct_decl(CowlFuncDataPropAxiom);

CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_get(CowlDataPropExp *prop);
CowlFuncDataPropAxiom* cowl_func_data_prop_axiom_retain(CowlFuncDataPropAxiom *axiom);
void cowl_func_data_prop_axiom_release(CowlFuncDataPropAxiom *axiom);

CowlDataPropExp* cowl_func_data_prop_axiom_get_prop(CowlFuncDataPropAxiom *axiom);

bool cowl_func_data_prop_axiom_equals(CowlFuncDataPropAxiom *lhs, CowlFuncDataPropAxiom *rhs);
cowl_uint_t cowl_func_data_prop_axiom_hash(CowlFuncDataPropAxiom *axiom);

bool cowl_func_data_prop_axiom_iterate_signature(CowlFuncDataPropAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_FUNC_DATA_PROP_AXIOM_H
