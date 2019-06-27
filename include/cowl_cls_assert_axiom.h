/// @author Ivano Bilenchi

#ifndef COWL_CLS_ASSERT_AXIOM_H
#define COWL_CLS_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlIndividual);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlClsAssertAxiom);

CowlClsAssertAxiom* cowl_cls_assert_axiom_get(CowlIndividual *ind, CowlClsExp *exp,
                                              CowlAnnotationVec *annot);
CowlClsAssertAxiom* cowl_cls_assert_axiom_retain(CowlClsAssertAxiom *axiom);
void cowl_cls_assert_axiom_release(CowlClsAssertAxiom *axiom);

CowlIndividual* cowl_cls_assert_axiom_get_ind(CowlClsAssertAxiom *axiom);
CowlClsExp* cowl_cls_assert_axiom_get_cls_exp(CowlClsAssertAxiom *axiom);
CowlAnnotationVec* cowl_cls_assert_axiom_get_annot(CowlClsAssertAxiom *axiom);

bool cowl_cls_assert_axiom_equals(CowlClsAssertAxiom *lhs, CowlClsAssertAxiom *rhs);
cowl_uint_t cowl_cls_assert_axiom_hash(CowlClsAssertAxiom *axiom);

bool cowl_cls_assert_axiom_iterate_signature(CowlClsAssertAxiom *axiom,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_CLS_ASSERT_AXIOM_H
