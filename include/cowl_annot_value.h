/**
 * Defines CowlAnnotValue and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ANNOT_VALUE_H
#define COWL_ANNOT_VALUE_H

#include "cowl_annot_value_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Represents annotation values, which can be either anonymous individuals, IRIs, or literals.
 *
 * @see CowlAnnotation
 */
typedef cowl_struct(CowlAnnotValue) {

    /// Type of the annotation value.
    CowlAnnotValueType type;

    /// Concrete value.
    union {

        /// IRI value.
        CowlIRI *iri;

        /// Anonymous individual value.
        CowlAnonInd *anon_ind;

        /// Literal value.
        CowlLiteral *literal;

    };

} CowlAnnotValue;

/**
 * Initializes an annotation value by wrapping the specified IRI.
 *
 * @param IRI [CowlIRI *] IRI to wrap.
 * @return [CowlAnnotValue] Annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_wrap_iri(IRI) \
    ((CowlAnnotValue const){ .type = COWL_AVT_IRI, .iri = (IRI)})

/**
 * Initializes an annotation value by wrapping the specified anonymous individual.
 *
 * @param IND [CowlAnonInd *] Anonymous Individual to wrap.
 * @return [CowlAnnotValue] Annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_wrap_anon_ind(IND) \
    ((CowlAnnotValue const){ .type = COWL_AVT_ANON_IND, .anon_ind = (CowlAnonInd *)(IND) })

/**
 * Initializes an annotation value by wrapping the specified literal.
 *
 * @param LITERAL [CowlLiteral *] Literal to wrap.
 * @return [CowlAnnotValue] Annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_wrap_literal(LITERAL) \
    ((CowlAnnotValue const){ .type = COWL_AVT_LITERAL, .literal = (LITERAL) })

/**
 * Initializes an annotation value by wrapping and retaining the specified IRI.
 *
 * @param IRI [CowlIRI *] IRI to wrap.
 * @return [CowlAnnotValue] Retained annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_init_iri(IRI) \
    cowl_annot_value_wrap_iri(cowl_iri_retain(IRI))

/**
 * Initializes an annotation value by wrapping and retaining the specified anonymous individual.
 *
 * @param IND [CowlAnonInd *] Anonymous Individual to wrap.
 * @return [CowlAnnotValue] Retained annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_init_anon_ind(IND) \
    cowl_annot_value_wrap_anon_ind(cowl_anon_ind_retain(IND))

/**
 * Initializes an annotation value by wrapping and retaining the specified literal.
 *
 * @param LITERAL [CowlLiteral *] Literal to wrap.
 * @return [CowlAnnotValue] Retained annotation value.
 *
 * @public @related CowlAnnotValue
 */
#define cowl_annot_value_init_literal(LITERAL) \
    cowl_annot_value_wrap_literal(cowl_literal_retain(LITERAL))

/**
 * Retains the underlying annotation value.
 *
 * @param value The annotation value.
 * @return Retained annotation value.
 *
 * @public @memberof CowlAnnotValue
 */
CowlAnnotValue cowl_annot_value_retain(CowlAnnotValue value);

/**
 * Releases the underlying annotation value.
 *
 * @param value The annotation value.
 *
 * @public @memberof CowlAnnotValue
 */
void cowl_annot_value_release(CowlAnnotValue value);

/**
 * Gets the string representation of the specified annotation value.
 *
 * @param value The annotation value.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlAnnotValue
 */
CowlString* cowl_annot_value_to_string(CowlAnnotValue value);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlAnnotValue
 */
bool cowl_annot_value_equals(CowlAnnotValue lhs, CowlAnnotValue rhs);

/**
 * Hash function.
 *
 * @param value The annotation value.
 * @return The hash value.
 *
 * @public @memberof CowlAnnotValue
 */
cowl_uint_t cowl_annot_value_hash(CowlAnnotValue value);

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_H
