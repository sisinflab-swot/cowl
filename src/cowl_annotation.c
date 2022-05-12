/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annotation_private.h"
#include "cowl_annot_prop.h"
#include "cowl_annot_value.h"
#include "cowl_hash_utils.h"
#include "cowl_template.h"
#include "cowl_vector.h"

static CowlAnnotation* cowl_annotation_alloc(CowlAnnotProp *prop, CowlAnnotValue *value,
                                             CowlVector *annot) {
    CowlAnnotation *annotation = ulib_alloc(annotation);
    if (!annotation) return NULL;

    (*annotation) = (CowlAnnotation) {
        .super = COWL_OBJECT_INIT(COWL_OT_ANNOTATION),
        .prop = cowl_annot_prop_retain(prop),
        .value = cowl_annot_value_retain(value),
        .annot = annot ? cowl_vector_retain(annot) : NULL
    };

    return annotation;
}

static void cowl_annotation_free(CowlAnnotation *annot) {
    cowl_annot_prop_release(annot->prop);
    cowl_annot_value_release(annot->value);
    if (annot->annot) cowl_vector_release(annot->annot);
    ulib_free(annot);
}

CowlAnnotation* cowl_annotation_get(CowlAnnotProp *prop, CowlAnnotValue *value,
                                    CowlVector *annot) {
    if (!(prop && value)) return NULL;
    return cowl_annotation_alloc(prop, value, annot);
}

CowlAnnotation* cowl_annotation_retain(CowlAnnotation *annot) {
    return cowl_object_incr_ref(annot);
}

void cowl_annotation_release(CowlAnnotation *annot) {
    if (annot && !cowl_object_decr_ref(annot)) {
        cowl_annotation_free(annot);
    }
}

CowlAnnotProp* cowl_annotation_get_prop(CowlAnnotation *annot) {
    return annot->prop;
}

CowlAnnotValue* cowl_annotation_get_value(CowlAnnotation *annot) {
    return annot->value;
}

CowlVector* cowl_annotation_get_annot(CowlAnnotation *annot) {
    return annot->annot;
}

CowlString* cowl_annotation_to_string(CowlAnnotation *annot)
    COWL_TO_STRING_IMPL(annotation, annot)

bool cowl_annotation_equals(CowlAnnotation *lhs, CowlAnnotation *rhs) {
    return cowl_annot_prop_equals(lhs->prop, rhs->prop) &&
           cowl_annot_value_equals(lhs->value, rhs->value) &&
           lhs->annot && rhs->annot && cowl_vector_equals(lhs->annot, rhs->annot);
}

ulib_uint cowl_annotation_hash(CowlAnnotation *annot) {
    return cowl_hash_2(COWL_HASH_INIT_ANNOTATION,
                       cowl_annot_prop_hash(annot->prop),
                       cowl_annot_value_hash(annot->value));
}

bool cowl_annotation_iterate_primitives(CowlAnnotation *annot, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return (cowl_annot_value_iterate_primitives(annot->value, flags, iter) &&
            cowl_annot_prop_iterate_primitives(annot->prop, flags, iter) &&
            cowl_vector_iterate_primitives(annot->annot, flags, iter));
}
