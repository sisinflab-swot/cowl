/**
 * Declares CowlAnnotProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_H
#define COWL_ANNOT_PROP_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotProp);
/// @endcond

/**
 * Represents an [AnnotationProperty] in the OWL 2 specification.
 *
 * [AnnotationProperty]: https://www.w3.org/TR/owl2-syntax/#Annotation_Properties
 *
 * @struct CowlAnnotProp
 * @extends CowlEntity
 */

/**
 * Returns a retained annotation property.
 *
 * @param iri IRI of the property.
 * @return Retained annotation property, or NULL on error.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
CowlAnnotProp *cowl_annot_prop(CowlIRI *iri) {
    return (CowlAnnotProp *)cowl_entity_get_impl(COWL_OT_ANNOT_PROP, iri);
}

/**
 * Returns a retained annotation property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained annotation property, or NULL on error.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
CowlAnnotProp *cowl_annot_prop_from_string(UString string) {
    return (CowlAnnotProp *)cowl_entity_from_string_impl(COWL_OT_ANNOT_PROP, string);
}

/**
 * Returns a retained annotation property given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlAnnotProp *] Retained annotation property, or NULL on error.
 *
 * @public @related CowlAnnotProp
 */
#define cowl_annot_prop_from_static(CSTR) cowl_annot_prop_from_string(ustring_literal(CSTR))

/**
 * Gets the IRI of the specified annotation property.
 *
 * @param prop The annotation property.
 * @return IRI of the annotation property.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
CowlIRI *cowl_annot_prop_get_iri(CowlAnnotProp *prop) {
    return cowl_entity_get_iri((CowlEntity *)prop);
}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_H
