/// @author Ivano Bilenchi

#ifndef COWL_ANNOTATION_VEC_H
#define COWL_ANNOTATION_VEC_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotation);
typedef CowlAnnotation* CowlAnnotationPtr;

VECTOR_DECL_EQUATABLE(CowlAnnotationPtr)
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

void cowl_annotation_vec_free(CowlAnnotationVec *vec);

bool cowl_annotation_vec_equals(CowlAnnotationVec *lhs, CowlAnnotationVec *rhs);
cowl_uint_t cowl_annotation_vec_hash(CowlAnnotationVec *vec);

bool cowl_annotation_vec_iterate_signature(CowlAnnotationVec *vec, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOTATION_VEC_H
