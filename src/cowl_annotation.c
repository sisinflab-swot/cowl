/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annotation_private.h"
#include "cowl_annot_prop.h"
#include "cowl_annot_value.h"
#include "cowl_hash_utils.h"
#include "cowl_object_vec_private.h"
#include "cowl_template.h"

static CowlAnnotation* cowl_annotation_alloc(CowlAnnotProp *prop, CowlAnnotValue *value,
                                             CowlObjectVec *annot) {
    CowlAnnotation *annotation = ulib_alloc(annotation);
    if (!annotation) return NULL;

    ulib_uint hash = cowl_hash_3(COWL_HASH_INIT_ANNOTATION,
                                 cowl_annot_prop_hash(prop),
                                 cowl_annot_value_hash(value),
                                 annot ? cowl_object_vec_hash(annot) : 0);

    (*annotation) = (CowlAnnotation) {
        .super = COWL_HASH_OBJECT_INIT(COWL_OT_ANNOTATION, hash),
        .prop = cowl_annot_prop_retain(prop),
        .value = cowl_annot_value_retain(value),
        .annot = annot
    };

    return annotation;
}

static void cowl_annotation_free(CowlAnnotation *annot) {
    cowl_annot_prop_release(annot->prop);
    cowl_annot_value_release(annot->value);
    cowl_object_vec_free_spec(annotation, annot->annot);
    ulib_free(annot);
}

CowlAnnotation* cowl_annotation_get(CowlAnnotProp *prop, CowlAnnotValue *value,
                                    CowlObjectVec *annot) {
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

CowlObjectVec* cowl_annotation_get_annot(CowlAnnotation *annot) {
    return annot->annot;
}

CowlString* cowl_annotation_to_string(CowlAnnotation *annot)
    COWL_TO_STRING_IMPL(annotation, annot)

bool cowl_annotation_equals(CowlAnnotation *lhs, CowlAnnotation *rhs) {
    return cowl_object_hash_equals(lhs, rhs) &&
           cowl_annot_prop_equals(lhs->prop, rhs->prop) &&
           cowl_annot_value_equals(lhs->value, rhs->value) &&
           cowl_object_vec_equals(lhs->annot, rhs->annot);
}

ulib_uint cowl_annotation_hash(CowlAnnotation *annot) {
    return cowl_object_hash_get(annot);
}

bool cowl_annotation_iterate_primitives(CowlAnnotation *annot, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return (cowl_annot_value_iterate_primitives(annot->value, flags, iter) &&
            cowl_annot_prop_iterate_primitives(annot->prop, flags, iter) &&
            cowl_object_vec_iterate_primitives(annot->annot, flags, iter));
}
