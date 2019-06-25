/// @author Ivano Bilenchi

#ifndef COWL_ANNOTATION_H
#define COWL_ANNOTATION_H

#include "cowl_annot_value.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotProp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlAnnotation);

CowlAnnotation* cowl_annotation_get(CowlAnnotProp *prop, CowlAnnotValue value,
                                    CowlAnnotationVec *annot);
CowlAnnotation* cowl_annotation_retain(CowlAnnotation *annot);
void cowl_annotation_release(CowlAnnotation *annot);

CowlAnnotProp* cowl_annotation_get_prop(CowlAnnotation *annot);
CowlAnnotValue cowl_annotation_get_value(CowlAnnotation *annot);
CowlAnnotationVec* cowl_annotation_get_annot(CowlAnnotation *annot);

bool cowl_annotation_equals(CowlAnnotation *lhs, CowlAnnotation *rhs);
cowl_uint_t cowl_annotation_hash(CowlAnnotation *annot);

bool cowl_annotation_iterate_signature(CowlAnnotation *annot, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_ANNOTATION_H
