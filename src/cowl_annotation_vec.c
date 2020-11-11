/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annotation_vec.h"
#include "cowl_annotation.h"
#include "cowl_hash_utils.h"

UVEC_IMPL_EQUATABLE(CowlAnnotationPtr, cowl_annotation_equals)

void cowl_annotation_vec_free(CowlAnnotationVec *vec) {
    if (!vec) return;
    uvec_foreach(CowlAnnotationPtr, vec, annot, cowl_annotation_release(annot));
    uvec_free(CowlAnnotationPtr, (UVec(CowlAnnotationPtr)*)vec);
}

bool cowl_annotation_vec_equals(CowlAnnotationVec *lhs, CowlAnnotationVec *rhs) {
    return uvec_equals(CowlAnnotationPtr, lhs, rhs);
}

cowl_uint cowl_annotation_vec_hash(CowlAnnotationVec *vec) {
    cowl_uint hash = 0;

    uvec_foreach(CowlAnnotationPtr, vec, annot, {
        hash = cowl_hash_iter(hash, cowl_annotation_hash(annot));
    });

    return hash;
}

bool cowl_annotation_vec_iterate_primitives(CowlAnnotationVec *vec, CowlIterator *iter,
                                            CowlPrimitiveFlags flags) {
    uvec_foreach(CowlAnnotationPtr, vec, annot, {
        if (!cowl_annotation_iterate_primitives(annot, iter, flags)) return false;
    });
    return true;
}
