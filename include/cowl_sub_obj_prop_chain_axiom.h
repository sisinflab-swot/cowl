/// @author Ivano Bilenchi

#ifndef COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
#define COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);

cowl_struct_decl(CowlSubObjPropChainAxiom);

CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_get(CowlObjPropExpVec *sub_props,
                                                            CowlObjPropExp *super_prop);
CowlSubObjPropChainAxiom* cowl_sub_obj_prop_chain_axiom_retain(CowlSubObjPropChainAxiom *axiom);
void cowl_sub_obj_prop_chain_axiom_release(CowlSubObjPropChainAxiom *axiom);

CowlObjPropExpVec* cowl_sub_obj_prop_chain_axiom_get_sub_props(CowlSubObjPropChainAxiom *axiom);
CowlObjPropExp* cowl_sub_obj_prop_chain_axiom_get_super_prop(CowlSubObjPropChainAxiom *axiom);

bool cowl_sub_obj_prop_chain_axiom_equals(CowlSubObjPropChainAxiom *lhs,
                                          CowlSubObjPropChainAxiom *rhs);
cowl_uint_t cowl_sub_obj_prop_chain_axiom_hash(CowlSubObjPropChainAxiom *axiom);

bool cowl_sub_obj_prop_chain_axiom_iterate_signature(CowlSubObjPropChainAxiom *axiom, void *ctx,
                                                     CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_CHAIN_AXIOM_H
