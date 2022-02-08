/**
 * Declares CowlAnnotProp and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_PROP_H
#define COWL_ANNOT_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlAnnotProp);
/// @endcond

/**
 * Represents an [AnnotationProperty] in the OWL 2 specification.
 *
 * [AnnotationProperty]: https://www.w3.org/TR/owl2-syntax/#Annotation_Properties
 *
 * @struct CowlAnnotProp
 */

/**
 * Returns a retained annotation property.
 *
 * @param iri IRI of the property.
 * @return Retained annotation property, or NULL on error.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri);

/**
 * Returns a retained annotation property given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Retained annotation property, or NULL on error.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
CowlAnnotProp* cowl_annot_prop_from_string(UString string);

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
 * Retains the specified annotation property.
 *
 * @param prop The annotation property.
 * @return Retained annotation property.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
CowlAnnotProp* cowl_annot_prop_retain(CowlAnnotProp *prop);

/**
 * Releases the specified annotation property.
 *
 * @param prop The annotation property.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
void cowl_annot_prop_release(CowlAnnotProp *prop);

/**
 * Gets the IRI of the specified annotation property.
 *
 * @param prop The annotation property.
 * @return IRI of the annotation property.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop);

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
COWL_PUBLIC
CowlString* cowl_annot_prop_to_string(CowlAnnotProp *prop);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs);

/**
 * Hash function.
 *
 * @param prop The annotation property.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
ulib_uint cowl_annot_prop_hash(CowlAnnotProp *prop);

/**
 * Iterates over this annotation property.
 *
 * @param prop The annotation property.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlAnnotProp
 */
COWL_PUBLIC
bool cowl_annot_prop_iterate_primitives(CowlAnnotProp *prop, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_H
