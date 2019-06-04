/// @author Ivano Bilenchi

#ifndef COWL_HAS_KEY_AXIOM_H
#define COWL_HAS_KEY_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlDataPropExpSet);
cowl_hash_decl(CowlObjPropExpSet);
cowl_struct_decl(CowlClsExp);

cowl_struct_decl(CowlHasKeyAxiom);

CowlHasKeyAxiom* cowl_has_key_axiom_get(CowlClsExp *cls_exp, CowlObjPropExpSet *obj_props,
                                        CowlDataPropExpSet *data_props);
CowlHasKeyAxiom* cowl_has_key_axiom_retain(CowlHasKeyAxiom *axiom);
void cowl_has_key_axiom_release(CowlHasKeyAxiom *axiom);

CowlClsExp* cowl_has_key_axiom_get_cls_exp(CowlHasKeyAxiom *axiom);
CowlObjPropExpSet* cowl_has_key_axiom_get_obj_props(CowlHasKeyAxiom *axiom);
CowlDataPropExpSet* cowl_has_key_axiom_get_data_props(CowlHasKeyAxiom *axiom);

bool cowl_has_key_axiom_equals(CowlHasKeyAxiom *lhs, CowlHasKeyAxiom *rhs);
cowl_uint_t cowl_has_key_axiom_hash(CowlHasKeyAxiom *axiom);

bool cowl_has_key_axiom_iterate_signature(CowlHasKeyAxiom *axiom, void *ctx,
                                          CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_HAS_KEY_AXIOM_H
