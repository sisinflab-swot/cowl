/// @author Ivano Bilenchi

#ifndef COWL_SUB_ANNOT_PROP_AXIOM_H
#define COWL_SUB_ANNOT_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlSubAnnotPropAxiom);

CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_get(CowlAnnotProp *sub, CowlAnnotProp *super,
                                                     CowlAnnotationVec *annot);
CowlSubAnnotPropAxiom* cowl_sub_annot_prop_axiom_retain(CowlSubAnnotPropAxiom *axiom);
void cowl_sub_annot_prop_axiom_release(CowlSubAnnotPropAxiom *axiom);

CowlAnnotProp* cowl_sub_annot_prop_axiom_get_super(CowlSubAnnotPropAxiom *axiom);
CowlAnnotProp* cowl_sub_annot_prop_axiom_get_sub(CowlSubAnnotPropAxiom *axiom);
CowlAnnotationVec* cowl_sub_annot_prop_axiom_get_annot(CowlSubAnnotPropAxiom *axiom);

bool cowl_sub_annot_prop_axiom_equals(CowlSubAnnotPropAxiom *lhs, CowlSubAnnotPropAxiom *rhs);
cowl_uint_t cowl_sub_annot_prop_axiom_hash(CowlSubAnnotPropAxiom *axiom);

bool cowl_sub_annot_prop_axiom_iterate_signature(CowlSubAnnotPropAxiom *axiom,
                                                 CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_ANNOT_PROP_AXIOM_H
