/// @author Ivano Bilenchi

#ifndef COWL_INV_OBJ_PROP_AXIOM_H
#define COWL_INV_OBJ_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlInvObjPropAxiom);

CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_get(CowlObjPropExp *first, CowlObjPropExp *second);
CowlInvObjPropAxiom* cowl_inv_obj_prop_axiom_retain(CowlInvObjPropAxiom *axiom);
void cowl_inv_obj_prop_axiom_release(CowlInvObjPropAxiom *axiom);

CowlObjPropExp* cowl_inv_obj_prop_axiom_get_first_prop(CowlInvObjPropAxiom *axiom);
CowlObjPropExp* cowl_inv_obj_prop_axiom_get_second_prop(CowlInvObjPropAxiom *axiom);

bool cowl_inv_obj_prop_axiom_equals(CowlInvObjPropAxiom *lhs, CowlInvObjPropAxiom *rhs);
cowl_uint_t cowl_inv_obj_prop_axiom_hash(CowlInvObjPropAxiom *axiom);

bool cowl_inv_obj_prop_axiom_iterate_signature(CowlInvObjPropAxiom *axiom,
                                               void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_INV_OBJ_PROP_AXIOM_H
