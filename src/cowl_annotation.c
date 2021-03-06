/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annotation_private.h"
#include "cowl_annotation_vec.h"
#include "cowl_annot_prop.h"
#include "cowl_annot_value.h"
#include "cowl_hash_utils.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlAnnotation* cowl_annotation_alloc(CowlAnnotProp *prop, CowlAnnotValue *value,
                                             CowlAnnotationVec *annot) {
    CowlAnnotation *annotation = cowl_alloc(annotation);
    if (!annotation) return NULL;

    cowl_uint hash = cowl_hash_3(COWL_HASH_INIT_ANNOTATION,
                                 cowl_annot_prop_hash(prop),
                                 cowl_annot_value_hash(value),
                                 annot ? cowl_annotation_vec_hash(annot) : 0);

    (*annotation) = (CowlAnnotation) {
        .super = COWL_HASH_OBJECT_INIT(COWL_OT_ANNOTATION, hash),
        .prop = cowl_annot_prop_retain(prop),
        .value = cowl_annot_value_retain(value),
        .annot = annot
    };

    return annotation;
}

static void cowl_annotation_free(CowlAnnotation *annot) {
    if (!annot) return;
    cowl_annot_prop_release(annot->prop);
    cowl_annot_value_release(annot->value);
    cowl_annotation_vec_free(annot->annot);
    cowl_free(annot);
}

CowlAnnotation* cowl_annotation_get(CowlAnnotProp *prop, CowlAnnotValue *value,
                                    CowlAnnotationVec *annot) {
    if (!(prop && value)) return NULL;
    return cowl_annotation_alloc(prop, value, annot);
}

CowlAnnotation* cowl_annotation_retain(CowlAnnotation *annot) {
    return cowl_object_retain(annot);
}

void cowl_annotation_release(CowlAnnotation *annot) {
    if (annot && !cowl_object_release(annot)) {
        cowl_annotation_free(annot);
    }
}

CowlAnnotProp* cowl_annotation_get_prop(CowlAnnotation *annot) {
    return annot->prop;
}

CowlAnnotValue* cowl_annotation_get_value(CowlAnnotation *annot) {
    return annot->value;
}

CowlAnnotationVec* cowl_annotation_get_annot(CowlAnnotation *annot) {
    return annot->annot;
}

CowlString* cowl_annotation_to_string(CowlAnnotation *annot)
    COWL_TO_STRING_IMPL(annotation, annot)

bool cowl_annotation_equals(CowlAnnotation *lhs, CowlAnnotation *rhs) {
    return cowl_annot_prop_equals(lhs->prop, rhs->prop) &&
           cowl_annot_value_equals(lhs->value, rhs->value) &&
           cowl_annotation_vec_equals(lhs->annot, rhs->annot);
}

cowl_uint cowl_annotation_hash(CowlAnnotation *annot) {
    return cowl_object_hash_get(annot);
}

bool cowl_annotation_iterate_primitives(CowlAnnotation *annot, CowlIterator *iter,
                                        CowlPrimitiveFlags flags) {
    return (cowl_annot_value_iterate_primitives(annot->value, iter, flags) &&
            cowl_annot_prop_iterate_primitives(annot->prop, iter, flags) &&
            cowl_annotation_vec_iterate_primitives(annot->annot, iter, flags));
}
