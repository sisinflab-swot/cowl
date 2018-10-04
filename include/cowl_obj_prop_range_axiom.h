/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_H
#define COWL_OBJ_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjPropRangeAxiom CowlObjPropRangeAxiom;

CowlObjPropExp const* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom const *axiom);
CowlClsExp const* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom const *axiom);

bool cowl_obj_prop_range_axiom_enum_signature(CowlObjPropRangeAxiom const *axiom, void *ctx,
                                              CowlEntityIterator iter);

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom const *lhs,
                                       CowlObjPropRangeAxiom const *rhs);
uint32_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom const *axiom);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_H
