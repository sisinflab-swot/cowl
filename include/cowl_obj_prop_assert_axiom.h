/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_ASSERT_AXIOM_H
#define COWL_OBJ_PROP_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIndividual CowlIndividual;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlObjPropAssertAxiom CowlObjPropAssertAxiom;

CowlIndividual const* cowl_obj_prop_assert_axiom_get_source(CowlObjPropAssertAxiom const *axiom);
CowlIndividual const* cowl_obj_prop_assert_axiom_get_target(CowlObjPropAssertAxiom const *axiom);
CowlObjPropExp const* cowl_obj_prop_assert_axiom_get_prop(CowlObjPropAssertAxiom const *axiom);

bool cowl_obj_prop_assert_axiom_equals(CowlObjPropAssertAxiom const *lhs,
                                       CowlObjPropAssertAxiom const *rhs);
uint32_t cowl_obj_prop_assert_axiom_hash(CowlObjPropAssertAxiom const *axiom);

bool cowl_obj_prop_assert_axiom_iterate_signature(CowlObjPropAssertAxiom const *axiom,
                                                  void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_ASSERT_AXIOM_H
