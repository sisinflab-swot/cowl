/// @author Ivano Bilenchi

#ifndef COWL_ANNOTATION_VEC_PRIVATE_H
#define COWL_ANNOTATION_VEC_PRIVATE_H

#include "cowl_annotation_vec.h"

COWL_BEGIN_DECLS

cowl_vector_decl_mutable(CowlAnnotationPtr, CowlMutableAnnotationVec);

void cowl_annotation_vec_push(CowlMutableAnnotationVec *vec, CowlAnnotation *annot);

COWL_END_DECLS

#endif // COWL_ANNOTATION_VEC_PRIVATE_H
