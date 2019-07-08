/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_xsd_vocab_private.h"
#include "cowl_iri_private.h"
#include "cowl_string.h"

#define CS_XSD_NS "http://www.w3.org/2001/XMLSchema#"
#define CS_XSD_LENGTH "length"
#define CS_XSD_MIN_LENGTH "minLength"
#define CS_XSD_MAX_LENGTH "maxLength"
#define CS_XSD_PATTERN "pattern"
#define CS_XSD_MIN_INCLUSIVE "minInclusive"
#define CS_XSD_MIN_EXCLUSIVE "minExclusive"
#define CS_XSD_MAX_INCLUSIVE "maxInclusive"
#define CS_XSD_MAX_EXCLUSIVE "maxExclusive"
#define CS_XSD_TOTAL_DIGITS "totalDigits"
#define CS_XSD_FRACTION_DIGITS "fractionDigits"
#define CS_XSD_LANG_RANGE "langRange"

static cowl_struct(CowlXSDVocab) vocab;

void cowl_xsd_vocab_init(void) {
    CowlString *xsd_ns_str = cowl_string_from_static(CS_XSD_NS);
    CowlString *xsd_length_str = cowl_string_from_static(CS_XSD_LENGTH);
    CowlString *xsd_min_length_str = cowl_string_from_static(CS_XSD_MIN_LENGTH);
    CowlString *xsd_max_length_str = cowl_string_from_static(CS_XSD_MAX_LENGTH);
    CowlString *xsd_pattern_str = cowl_string_from_static(CS_XSD_PATTERN);
    CowlString *xsd_min_inclusive_str = cowl_string_from_static(CS_XSD_MIN_INCLUSIVE);
    CowlString *xsd_min_exclusive_str = cowl_string_from_static(CS_XSD_MIN_EXCLUSIVE);
    CowlString *xsd_max_inclusive_str = cowl_string_from_static(CS_XSD_MAX_INCLUSIVE);
    CowlString *xsd_max_exclusive_str = cowl_string_from_static(CS_XSD_MAX_EXCLUSIVE);
    CowlString *xsd_total_digits_str = cowl_string_from_static(CS_XSD_TOTAL_DIGITS);
    CowlString *xsd_fraction_digits_str = cowl_string_from_static(CS_XSD_FRACTION_DIGITS);
    CowlString *xsd_lang_range_str = cowl_string_from_static(CS_XSD_LANG_RANGE);

    vocab = (cowl_struct(CowlXSDVocab)) {
        .ns = xsd_ns_str,

        .iri = {
            .length = cowl_iri_get(xsd_ns_str, xsd_length_str),
            .min_length = cowl_iri_get(xsd_ns_str, xsd_min_length_str),
            .max_length = cowl_iri_get(xsd_ns_str, xsd_max_length_str),
            .pattern = cowl_iri_get(xsd_ns_str, xsd_pattern_str),
            .min_inclusive = cowl_iri_get(xsd_ns_str, xsd_min_inclusive_str),
            .min_exclusive = cowl_iri_get(xsd_ns_str, xsd_min_exclusive_str),
            .max_inclusive = cowl_iri_get(xsd_ns_str, xsd_max_inclusive_str),
            .max_exclusive = cowl_iri_get(xsd_ns_str, xsd_max_exclusive_str),
            .total_digits = cowl_iri_get(xsd_ns_str, xsd_total_digits_str),
            .fraction_digits = cowl_iri_get(xsd_ns_str, xsd_fraction_digits_str),
            .lang_range = cowl_iri_get(xsd_ns_str, xsd_lang_range_str)
        }
    };
}

void cowl_xsd_vocab_deinit(void) {
    cowl_string_release(vocab.ns);
    cowl_iri_release(vocab.iri.length);
    cowl_iri_release(vocab.iri.min_length);
    cowl_iri_release(vocab.iri.max_length);
    cowl_iri_release(vocab.iri.pattern);
    cowl_iri_release(vocab.iri.min_inclusive);
    cowl_iri_release(vocab.iri.min_exclusive);
    cowl_iri_release(vocab.iri.max_inclusive);
    cowl_iri_release(vocab.iri.max_exclusive);
    cowl_iri_release(vocab.iri.total_digits);
    cowl_iri_release(vocab.iri.fraction_digits);
    cowl_iri_release(vocab.iri.lang_range);
}

CowlXSDVocab* cowl_xsd_vocab_get(void) {
    return &vocab;
}
