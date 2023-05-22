/**
 * Declares CowlAnnotation and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOTATION_H
#define COWL_ANNOTATION_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnnotValue);
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [Annotation] in the OWL 2 specification.
 *
 * [Annotation]: https://www.w3.org/TR/owl2-syntax/#Annotations
 *
 * @struct CowlAnnotation
 * @extends CowlObject
 */

/**
 * Returns a retained annotation.
 *
 * @param prop The annotation property.
 * @param value The annotation value.
 * @param annot [optional] The annotations.
 * @return Retained annotation, or NULL on error.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
CowlAnnotation *cowl_annotation(CowlAnnotProp *prop, CowlAnyAnnotValue *value, CowlVector *annot) {
    return (CowlAnnotation *)cowl_get_impl_2_annot(COWL_OT_ANNOTATION, prop, value, annot);
}

/**
 * Gets the annotation property.
 *
 * @param annot The annotation.
 * @return The annotation property.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
CowlAnnotProp *cowl_annotation_get_prop(CowlAnnotation *annot) {
    return (CowlAnnotProp *)cowl_get_field(annot, 0);
}

/**
 * Gets the annotation value.
 *
 * @param annot The annotation.
 * @return The annotation value.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
CowlAnnotValue *cowl_annotation_get_value(CowlAnnotation *annot) {
    return (CowlAnnotValue *)cowl_get_field(annot, 1);
}

/**
 * Gets the annotations of the specified annotation.
 *
 * @param annot The annotation.
 * @return The annotations.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
CowlVector *cowl_annotation_get_annot(CowlAnnotation *annot) {
    return (CowlVector *)cowl_get_opt_field(annot);
}

/**
 * Returns the string representation of the specified annotation.
 *
 * @param annot The annotation.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
CowlString *cowl_annotation_to_string(CowlAnnotation *annot) {
    return cowl_to_string(annot);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
bool cowl_annotation_equals(CowlAnnotation *lhs, CowlAnnotation *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param annot The annotation.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotation
 */
COWL_INLINE
ulib_uint cowl_annotation_hash(CowlAnnotation *annot) {
    return cowl_hash_impl(annot);
}

COWL_END_DECLS

#endif // COWL_ANNOTATION_H
