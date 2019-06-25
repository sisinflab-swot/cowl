/// @author Ivano Bilenchi

#ifndef COWL_ANNOTATION_PRIVATE_H
#define COWL_ANNOTATION_PRIVATE_H

#include "cowl_annotation.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnnotation) {
    CowlHashObject super;
    CowlAnnotProp *prop;
    CowlAnnotValue value;
    CowlAnnotationVec *annot;
};

COWL_END_DECLS

#endif // COWL_ANNOTATION_PRIVATE_H
