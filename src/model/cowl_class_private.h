/// @author Ivano Bilenchi

#ifndef COWL_CLASS_PRIVATE_H
#define COWL_CLASS_PRIVATE_H

#include "cowl_class.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

typedef struct CowlClass {
    CowlClsExp super;
    CowlIRI const *iri;
} CowlClass;

COWL_END_DECLS

#endif // COWL_CLASS_PRIVATE_H
