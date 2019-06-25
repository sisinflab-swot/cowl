/// @author Ivano Bilenchi

#ifndef COWL_NARY_CLS_AXIOM_H
#define COWL_NARY_CLS_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlClsExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlNAryClsAxiom);

CowlNAryClsAxiom* cowl_nary_cls_axiom_get(CowlNAryAxiomType type, CowlClsExpSet *classes,
                                          CowlAnnotationVec *annot);
CowlNAryClsAxiom* cowl_nary_cls_axiom_retain(CowlNAryClsAxiom *axiom);
void cowl_nary_cls_axiom_release(CowlNAryClsAxiom *axiom);

CowlNAryAxiomType cowl_nary_cls_axiom_get_type(CowlNAryClsAxiom *axiom);
CowlClsExpSet* cowl_nary_cls_axiom_get_classes(CowlNAryClsAxiom *axiom);
CowlAnnotationVec* cowl_nary_cls_axiom_get_annot(CowlNAryClsAxiom *axiom);

bool cowl_nary_cls_axiom_equals(CowlNAryClsAxiom *lhs, CowlNAryClsAxiom *rhs);
cowl_uint_t cowl_nary_cls_axiom_hash(CowlNAryClsAxiom *axiom);

bool cowl_nary_cls_axiom_iterate_signature(CowlNAryClsAxiom *axiom,
                                           void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_CLS_AXIOM_H
