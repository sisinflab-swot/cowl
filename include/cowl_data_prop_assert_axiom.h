/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_H
#define COWL_DATA_PROP_ASSERT_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlLiteral);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlDataPropAssertAxiom);

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                         CowlDataPropExp *prop,
                                                         CowlLiteral *obj,
                                                         CowlAnnotationVec *annot);
CowlDataPropAssertAxiom* cowl_neg_data_prop_assert_axiom_get(CowlIndividual *subj,
                                                             CowlDataPropExp *prop,
                                                             CowlLiteral *obj,
                                                             CowlAnnotationVec *annot);

CowlDataPropAssertAxiom* cowl_data_prop_assert_axiom_retain(CowlDataPropAssertAxiom *axiom);
void cowl_data_prop_assert_axiom_release(CowlDataPropAssertAxiom *axiom);

bool cowl_data_prop_assert_axiom_is_negative(CowlDataPropAssertAxiom *axiom);
CowlIndividual* cowl_data_prop_assert_axiom_get_subject(CowlDataPropAssertAxiom *axiom);
CowlLiteral* cowl_data_prop_assert_axiom_get_object(CowlDataPropAssertAxiom *axiom);
CowlDataPropExp* cowl_data_prop_assert_axiom_get_prop(CowlDataPropAssertAxiom *axiom);
CowlAnnotationVec* cowl_data_prop_assert_axiom_get_annot(CowlDataPropAssertAxiom *axiom);

bool cowl_data_prop_assert_axiom_equals(CowlDataPropAssertAxiom *lhs, CowlDataPropAssertAxiom *rhs);
cowl_uint_t cowl_data_prop_assert_axiom_hash(CowlDataPropAssertAxiom *axiom);

bool cowl_data_prop_assert_axiom_iterate_signature(CowlDataPropAssertAxiom *axiom,
                                                   CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_H
