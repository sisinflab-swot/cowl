/**
 * Declares CowlAnnotationVec and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOTATION_VEC_H
#define COWL_ANNOTATION_VEC_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);

typedef CowlAnnotation* CowlAnnotationPtr;
UVEC_DECL_EQUATABLE_SPEC(CowlAnnotationPtr, COWL_PUBLIC)
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
/// @endcond

/**
 * Vector of CowlAnnotation * elements.
 *
 * @struct CowlAnnotationVec
 * @extends Vector
 */

/**
 * Deallocates the specified vector, releasing its elements.
 *
 * @param vec The vector.
 *
 * @public @memberof CowlAnnotationVec
 */
COWL_PUBLIC
void cowl_annotation_vec_free(CowlAnnotationVec *vec);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotationVec
 */
COWL_PUBLIC
bool cowl_annotation_vec_equals(CowlAnnotationVec *lhs, CowlAnnotationVec *rhs);

/**
 * Hash function.
 *
 * @param vec The vector.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotationVec
 */
COWL_PUBLIC
cowl_uint_t cowl_annotation_vec_hash(CowlAnnotationVec *vec);

/**
 * Iterates over the primitives referenced by the specified vector.
 *
 * @param vec The vector.
 * @param iter The iterator.
 * @param flags Iteration flags.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotationVec
 */
COWL_PUBLIC
bool cowl_annotation_vec_iterate_primitives(CowlAnnotationVec *vec, CowlIterator *iter,
                                            CowlPrimitiveFlags flags);

COWL_END_DECLS

#endif // COWL_ANNOTATION_VEC_H
