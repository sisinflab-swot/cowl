/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_CHAR_AXIOM_H
#define COWL_OBJ_PROP_CHAR_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_obj_prop_char_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlObjPropCharAxiom);

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_get(CowlObjPropCharAxiomType type,
                                                   CowlObjPropExp *prop,
                                                   CowlAnnotationVec *annot);
CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_retain(CowlObjPropCharAxiom *axiom);
void cowl_obj_prop_char_axiom_release(CowlObjPropCharAxiom *axiom);

CowlObjPropCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom);
CowlObjPropExp* cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom);
CowlAnnotationVec* cowl_obj_prop_char_axiom_get_annot(CowlObjPropCharAxiom *axiom);

bool cowl_obj_prop_char_axiom_equals(CowlObjPropCharAxiom *lhs, CowlObjPropCharAxiom *rhs);
cowl_uint_t cowl_obj_prop_char_axiom_hash(CowlObjPropCharAxiom *axiom);

bool cowl_obj_prop_char_axiom_iterate_signature(CowlObjPropCharAxiom *axiom,
                                                CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_CHAR_AXIOM_H
