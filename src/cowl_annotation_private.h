/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOTATION_PRIVATE_H
#define COWL_ANNOTATION_PRIVATE_H

#include "cowl_annotation.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnnotation) {
    CowlHashObject super;
    CowlAnnotProp *prop;
    CowlAnnotValue *value;
    CowlObjectVec *annot;
};

COWL_END_DECLS

#endif // COWL_ANNOTATION_PRIVATE_H
