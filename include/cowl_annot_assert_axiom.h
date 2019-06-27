/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_ASSERT_AXIOM_H
#define COWL_ANNOT_ASSERT_AXIOM_H

#include "cowl_annot_value.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlAnnotAssertAxiom);

CowlAnnotAssertAxiom* cowl_annot_assert_axiom_get(CowlAnnotValue subject, CowlAnnotProp *prop,
                                                  CowlAnnotValue value, CowlAnnotationVec *annot);
CowlAnnotAssertAxiom* cowl_annot_assert_axiom_retain(CowlAnnotAssertAxiom *axiom);
void cowl_annot_assert_axiom_release(CowlAnnotAssertAxiom *axiom);

CowlAnnotValue cowl_annot_assert_axiom_get_subject(CowlAnnotAssertAxiom *axiom);
CowlAnnotValue cowl_annot_assert_axiom_get_value(CowlAnnotAssertAxiom *axiom);
CowlAnnotProp* cowl_annot_assert_axiom_get_prop(CowlAnnotAssertAxiom *axiom);
CowlAnnotationVec* cowl_annot_assert_axiom_get_annot(CowlAnnotAssertAxiom *axiom);

bool cowl_annot_assert_axiom_equals(CowlAnnotAssertAxiom *lhs, CowlAnnotAssertAxiom *rhs);
cowl_uint_t cowl_annot_assert_axiom_hash(CowlAnnotAssertAxiom *axiom);

bool cowl_annot_assert_axiom_iterate_signature(CowlAnnotAssertAxiom *axiom,
                                               CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_ASSERT_AXIOM_H
