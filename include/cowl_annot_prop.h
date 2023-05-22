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

/**
 * Returns the string representation of the specified annotation property.
 *
 * @param prop The annotation property.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
CowlString *cowl_annot_prop_to_string(CowlAnnotProp *prop) {
    return cowl_entity_to_string((CowlEntity *)prop);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs) {
    return lhs == rhs;
}

/**
 * Hash function.
 *
 * @param prop The annotation property.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_INLINE
ulib_uint cowl_annot_prop_hash(CowlAnnotProp *prop) {
    return uhash_ptr_hash(prop);
}

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_H
