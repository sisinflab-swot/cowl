/// @author Ivano Bilenchi

#ifndef COWL_SUB_CLS_AXIOM_H
#define COWL_SUB_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlSubClsAxiom);

CowlSubClsAxiom* cowl_sub_cls_axiom_get(CowlClsExp *sub, CowlClsExp *super,
                                        CowlAnnotationVec *annot);
CowlSubClsAxiom* cowl_sub_cls_axiom_retain(CowlSubClsAxiom *axiom);
void cowl_sub_cls_axiom_release(CowlSubClsAxiom *axiom);

CowlClsExp* cowl_sub_cls_axiom_get_super(CowlSubClsAxiom *axiom);
CowlClsExp* cowl_sub_cls_axiom_get_sub(CowlSubClsAxiom *axiom);
CowlAnnotationVec* cowl_sub_cls_axiom_get_annot(CowlSubClsAxiom *axiom);

bool cowl_sub_cls_axiom_equals(CowlSubClsAxiom *lhs, CowlSubClsAxiom *rhs);
cowl_uint_t cowl_sub_cls_axiom_hash(CowlSubClsAxiom *axiom);

bool cowl_sub_cls_axiom_iterate_signature(CowlSubClsAxiom *axiom, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_SUB_CLS_AXIOM_H
