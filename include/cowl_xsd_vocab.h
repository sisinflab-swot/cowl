/**
 * Defines CowlXSDVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_XSD_VOCAB_H
#define COWL_XSD_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// The XSD vocabulary.
typedef cowl_struct(CowlXSDVocab) {

    /// XSD namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// xsd:length
        CowlIRI *length;

        /// xsd:minLength
        CowlIRI *min_length;

        /// xsd:maxLength
        CowlIRI *max_length;

        /// xsd:pattern
        CowlIRI *pattern;

        /// xsd:minInclusive
        CowlIRI *min_inclusive;

        /// xsd:minExclusive
        CowlIRI *min_exclusive;

        /// xsd:maxInclusive
        CowlIRI *max_inclusive;

        /// xsd:maxExclusive
        CowlIRI *max_exclusive;

        /// xsd:totalDigits
        CowlIRI *total_digits;

        /// xsd:fractionDigits
        CowlIRI *fraction_digits;

        /// xsd:langRange
        CowlIRI *lang_range;

    } iri;

} const CowlXSDVocab;

/**
 * Gets the XSD vocabulary.
 *
 * @return The XSD vocabulary.
 *
 * @public @memberof CowlXSDVocab
 */
COWL_PUBLIC
CowlXSDVocab* cowl_xsd_vocab_get(void);

COWL_END_DECLS

#endif // COWL_XSD_VOCAB_H
