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

VECTOR_IMPL_EQUATABLE(CowlAnnotationPtr, cowl_annotation_equals)

void cowl_annotation_vec_free(CowlAnnotationVec *vec) {
    if (!vec) return;
    vector_foreach(CowlAnnotationPtr, vec, annot, cowl_annotation_release(annot));
    vector_free(CowlAnnotationPtr, (Vector(CowlAnnotationPtr)*)vec);
}

bool cowl_annotation_vec_equals(CowlAnnotationVec *lhs, CowlAnnotationVec *rhs) {
    return vector_equals(CowlAnnotationPtr, lhs, rhs);
}

cowl_uint_t cowl_annotation_vec_hash(CowlAnnotationVec *vec) {
    cowl_uint_t hash = 0;

    vector_foreach(CowlAnnotationPtr, vec, annot, {
        hash = cowl_hash_iter(hash, cowl_annotation_hash(annot));
    });

    return hash;
}

bool cowl_annotation_vec_iterate_primitives(CowlAnnotationVec *vec, CowlIterator *iter,
                                            CowlPrimitiveFlags flags) {
    vector_foreach(CowlAnnotationPtr, vec, annot, {
        if (!cowl_annotation_iterate_primitives(annot, iter, flags)) return false;
    });
    return true;
}
