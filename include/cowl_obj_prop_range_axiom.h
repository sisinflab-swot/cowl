/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_H
#define COWL_OBJ_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp CowlClsExp;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjPropRangeAxiom CowlObjPropRangeAxiom;

CowlObjPropRangeAxiom const* cowl_obj_prop_range_axiom_get(CowlObjPropExp const *prop,
                                                           CowlClsExp const *range);
CowlObjPropRangeAxiom const* cowl_obj_prop_range_axiom_retain(CowlObjPropRangeAxiom const *axiom);
void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom const *axiom);

CowlObjPropExp const* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom const *axiom);
CowlClsExp const* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom const *axiom);

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom const *lhs,
                                       CowlObjPropRangeAxiom const *rhs);
uint32_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom const *axiom);

bool cowl_obj_prop_range_axiom_iterate_signature(CowlObjPropRangeAxiom const *axiom,
                                                 void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_H
