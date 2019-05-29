/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_ASSERT_AXIOM_H
#define COWL_OBJ_PROP_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);

cowl_struct_decl(CowlObjPropAssertAxiom);

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_get(CowlIndividual *source,
                                                       CowlObjPropExp *prop,
                                                       CowlIndividual *target);
CowlObjPropAssertAxiom* cowl_neg_obj_prop_assert_axiom_get(CowlIndividual *source,
                                                           CowlObjPropExp *prop,
                                                           CowlIndividual *target);

CowlObjPropAssertAxiom* cowl_obj_prop_assert_axiom_retain(CowlObjPropAssertAxiom *axiom);
void cowl_obj_prop_assert_axiom_release(CowlObjPropAssertAxiom *axiom);

bool cowl_obj_prop_assert_axiom_is_negative(CowlObjPropAssertAxiom *axiom);
CowlIndividual* cowl_obj_prop_assert_axiom_get_source(CowlObjPropAssertAxiom *axiom);
CowlIndividual* cowl_obj_prop_assert_axiom_get_target(CowlObjPropAssertAxiom *axiom);
CowlObjPropExp* cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom *axiom);

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom *lhs, CowlObjPropAssertAxiom *rhs);
cowl_uint_t cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom *axiom);

bool cowl_obj_prop_assert_axiom_iterate_signature(CowlObjPropAssertAxiom *axiom,
                                                  void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_ASSERT_AXIOM_H
