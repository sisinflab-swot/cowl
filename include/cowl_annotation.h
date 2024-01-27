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
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [Annotation] in the OWL 2 specification.
 *
 * [Annotation]: https://www.w3.org/TR/owl2-syntax/#Annotations
 *
 * @superstruct{CowlObject}
 * @struct CowlAnnotation
 */
cowl_struct_decl(CowlAnnotation);

/**
 * @defgroup CowlAnnotation CowlAnnotation API
 * @{
 */

/**
 * Returns an annotation.
 *
 * @param prop The annotation property.
 * @param value The annotation value.
 * @param annot @type{optional} The annotations.
 * @return Annotation, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlAnnotation *cowl_annotation(CowlAnnotProp *prop, CowlAnyAnnotValue *value, CowlVector *annot) {
    return (CowlAnnotation *)cowl_get_impl_2_annot(COWL_OT_ANNOTATION, prop, value, annot);
}

/**
 * Gets the annotation property.
 *
 * @param annot The annotation.
 * @return The annotation property.
 */
COWL_PURE
COWL_INLINE
CowlAnnotProp *cowl_annotation_get_prop(CowlAnnotation *annot) {
    return (CowlAnnotProp *)cowl_get_field(annot, 0);
}

/**
 * Gets the annotation value.
 *
 * @param annot The annotation.
 * @return The annotation value.
 */
COWL_PURE
COWL_INLINE
CowlAnnotValue *cowl_annotation_get_value(CowlAnnotation *annot) {
    return (CowlAnnotValue *)cowl_get_field(annot, 1);
}

/**
 * Gets the annotations of the specified annotation.
 *
 * @param annot The annotation.
 * @return The annotations, or NULL of the annotation has no annotations.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_annotation_get_annot(CowlAnnotation *annot) {
    return (CowlVector *)cowl_get_opt_field(annot);
}

/// @}

COWL_END_DECLS

#endif // COWL_ANNOTATION_H
