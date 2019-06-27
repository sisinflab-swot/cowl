/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_RANGE_AXIOM_H
#define COWL_ANNOT_PROP_RANGE_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlAnnotPropRangeAxiom);

CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_get(CowlAnnotProp *prop, CowlIRI *range,
                                                         CowlAnnotationVec *annot);
CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_retain(CowlAnnotPropRangeAxiom *axiom);
void cowl_annot_prop_range_axiom_release(CowlAnnotPropRangeAxiom *axiom);

CowlAnnotProp* cowl_annot_prop_range_axiom_get_prop(CowlAnnotPropRangeAxiom *axiom);
CowlIRI* cowl_annot_prop_range_axiom_get_range(CowlAnnotPropRangeAxiom *axiom);
CowlAnnotationVec* cowl_annot_prop_range_axiom_get_annot(CowlAnnotPropRangeAxiom *axiom);

bool cowl_annot_prop_range_axiom_equals(CowlAnnotPropRangeAxiom *lhs,
                                        CowlAnnotPropRangeAxiom *rhs);
cowl_uint_t cowl_annot_prop_range_axiom_hash(CowlAnnotPropRangeAxiom *axiom);

bool cowl_annot_prop_range_axiom_iterate_signature(CowlAnnotPropRangeAxiom *axiom,
                                                   CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_RANGE_AXIOM_H
