/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_RANGE_AXIOM_H
#define COWL_OBJ_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjPropRangeAxiom const CowlObjPropRangeAxiom;

CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_get(CowlObjPropExp *prop, CowlClsExp *range);
CowlObjPropRangeAxiom* cowl_obj_prop_range_axiom_retain(CowlObjPropRangeAxiom *axiom);
void cowl_obj_prop_range_axiom_release(CowlObjPropRangeAxiom *axiom);

CowlObjPropExp* cowl_obj_prop_range_axiom_get_prop(CowlObjPropRangeAxiom *axiom);
CowlClsExp* cowl_obj_prop_range_axiom_get_range(CowlObjPropRangeAxiom *axiom);

bool cowl_obj_prop_range_axiom_equals(CowlObjPropRangeAxiom *lhs, CowlObjPropRangeAxiom *rhs);
cowl_uint_t cowl_obj_prop_range_axiom_hash(CowlObjPropRangeAxiom *axiom);

bool cowl_obj_prop_range_axiom_iterate_signature(CowlObjPropRangeAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_RANGE_AXIOM_H
