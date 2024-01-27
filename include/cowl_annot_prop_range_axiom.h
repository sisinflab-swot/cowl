/**
 * Declares CowlAnnotPropRangeAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_RANGE_AXIOM_H
#define COWL_ANNOT_PROP_RANGE_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlIRI);
/// @endcond

/**
 * Represents an [AnnotationPropertyRange] axiom in the OWL 2 specification.
 *
 * [AnnotationPropertyRange]: https://www.w3.org/TR/owl2-syntax/#Annotation_Property_Range
 *
 * @superstruct{CowlAxiom}
 * @struct CowlAnnotPropRangeAxiom
 */
cowl_struct_decl(CowlAnnotPropRangeAxiom);

/**
 * @defgroup CowlAnnotPropRangeAxiom CowlAnnotPropRangeAxiom API
 * @{
 */

/**
 * Returns an annotation property range axiom.
 *
 * @param prop The annotation property.
 * @param range Range of the annotation property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlAnnotPropRangeAxiom *
cowl_annot_prop_range_axiom(CowlAnnotProp *prop, CowlIRI *range, CowlVector *annot) {
    return (CowlAnnotPropRangeAxiom *)cowl_get_impl_2_annot(COWL_OT_A_ANNOT_PROP_RANGE, prop, range,
                                                            annot);
}

/**
 * Gets the annotation property.
 *
 * @param axiom The axiom.
 * @return The annotation property.
 */
COWL_PURE
COWL_INLINE
CowlAnnotProp *cowl_annot_prop_range_axiom_get_prop(CowlAnnotPropRangeAxiom *axiom) {
    return (CowlAnnotProp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the annotation property.
 *
 * @param axiom The axiom.
 * @return Range of the annotation property.
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_annot_prop_range_axiom_get_range(CowlAnnotPropRangeAxiom *axiom) {
    return (CowlIRI *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_RANGE_AXIOM_H
