/// @author Ivano Bilenchi

#ifndef COWL_SUB_OBJ_PROP_AXIOM_H
#define COWL_SUB_OBJ_PROP_AXIOM_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlSubObjPropAxiom);

CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_get(CowlObjPropExp *sub, CowlObjPropExp *super,
                                                 CowlAnnotationVec *annot);
CowlSubObjPropAxiom* cowl_sub_obj_prop_axiom_retain(CowlSubObjPropAxiom *axiom);
void cowl_sub_obj_prop_axiom_release(CowlSubObjPropAxiom *axiom);

CowlObjPropExp* cowl_sub_obj_prop_axiom_get_super(CowlSubObjPropAxiom *axiom);
CowlObjPropExp* cowl_sub_obj_prop_axiom_get_sub(CowlSubObjPropAxiom *axiom);
CowlAnnotationVec* cowl_sub_obj_prop_axiom_get_annot(CowlSubObjPropAxiom *axiom);

bool cowl_sub_obj_prop_axiom_equals(CowlSubObjPropAxiom *lhs, CowlSubObjPropAxiom *rhs);
cowl_uint_t cowl_sub_obj_prop_axiom_hash(CowlSubObjPropAxiom *axiom);

bool cowl_sub_obj_prop_axiom_iterate_signature(CowlSubObjPropAxiom *axiom,
                                               void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_SUB_OBJ_PROP_AXIOM_H
