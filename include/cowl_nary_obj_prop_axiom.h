/// @author Ivano Bilenchi

#ifndef COWL_NARY_OBJ_PROP_AXIOM_H
#define COWL_NARY_OBJ_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlObjPropExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlNAryObjPropAxiom);

CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_get(CowlNAryAxiomType type,
                                                   CowlObjPropExpSet *props,
                                                   CowlAnnotationVec *annot);
CowlNAryObjPropAxiom* cowl_nary_obj_prop_axiom_retain(CowlNAryObjPropAxiom *axiom);
void cowl_nary_obj_prop_axiom_release(CowlNAryObjPropAxiom *axiom);

CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom);
CowlObjPropExpSet* cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom);
CowlAnnotationVec* cowl_nary_obj_prop_axiom_get_annot(CowlNAryObjPropAxiom *axiom);

bool cowl_nary_obj_prop_axiom_equals(CowlNAryObjPropAxiom *lhs, CowlNAryObjPropAxiom *rhs);
cowl_uint_t cowl_nary_obj_prop_axiom_hash(CowlNAryObjPropAxiom *axiom);

bool cowl_nary_obj_prop_axiom_iterate_signature(CowlNAryObjPropAxiom *axiom,
                                                void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_H
