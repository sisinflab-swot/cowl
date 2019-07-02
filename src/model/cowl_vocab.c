/// @author Ivano Bilenchi

#include "cowl_vocab_private.h"
#include "cowl_class.h"
#include "cowl_datatype.h"
#include "cowl_iri.h"
#include "cowl_string.h"

#define CS_OWL_NS "http://www.w3.org/2002/07/owl#"
#define CS_RDF_NS "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define CS_XSD_NS "http://www.w3.org/2001/XMLSchema#"

#define CS_OWL_THING_REM "Thing"
#define CS_OWL_NOTHING_REM "Nothing"
#define CS_RDF_PLAIN_LITERAL_REM "PlainLiteral"

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

static cowl_struct(CowlOWLVocab) owl;
static cowl_struct(CowlRDFVocab) rdf;
static cowl_struct(CowlXSDVocab) xsd;

void cowl_vocab_init(void) {
    CowlString *owl_ns_str = cowl_string_from_static(CS_OWL_NS);
    CowlString *rdf_ns_str = cowl_string_from_static(CS_RDF_NS);
    CowlString *xsd_ns_str = cowl_string_from_static(CS_XSD_NS);

    CowlString *owl_thing_str = cowl_string_from_static(CS_OWL_THING_REM);
    CowlString *owl_nothing_str = cowl_string_from_static(CS_OWL_NOTHING_REM);

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

    CowlString *rdf_plain_literal_str = cowl_string_from_static(CS_RDF_PLAIN_LITERAL_REM);

    CowlIRI *owl_thing_iri = cowl_iri_get(owl_ns_str, owl_thing_str);
    CowlIRI *owl_nothing_iri = cowl_iri_get(owl_ns_str, owl_nothing_str);
    CowlIRI *rdf_plain_literal_iri = cowl_iri_get(rdf_ns_str, rdf_plain_literal_str);

    owl = (cowl_struct(CowlOWLVocab)) {
        .ns = owl_ns_str,

        .iri = {
            .thing = owl_thing_iri,
            .nothing = owl_nothing_iri
        },

        .cls = {
            .thing = cowl_class_get(owl_thing_iri),
            .nothing = cowl_class_get(owl_nothing_iri)
        }
    };

    rdf = (cowl_struct(CowlRDFVocab)) {
        .ns = rdf_ns_str,

        .iri = {
            .plain_literal = rdf_plain_literal_iri
        },

        .dt = {
            .plain_literal = cowl_datatype_get(rdf_plain_literal_iri)
        }
    };

    xsd = (cowl_struct(CowlXSDVocab)) {
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

void cowl_vocab_deinit(void) {
    cowl_string_release(owl.ns);
    cowl_string_release(rdf.ns);
    cowl_string_release(xsd.ns);

    cowl_iri_release(owl.iri.thing);
    cowl_iri_release(owl.iri.nothing);
    cowl_iri_release(rdf.iri.plain_literal);
    cowl_iri_release(xsd.iri.length);
    cowl_iri_release(xsd.iri.min_length);
    cowl_iri_release(xsd.iri.max_length);
    cowl_iri_release(xsd.iri.pattern);
    cowl_iri_release(xsd.iri.min_inclusive);
    cowl_iri_release(xsd.iri.min_exclusive);
    cowl_iri_release(xsd.iri.max_inclusive);
    cowl_iri_release(xsd.iri.max_exclusive);
    cowl_iri_release(xsd.iri.total_digits);
    cowl_iri_release(xsd.iri.fraction_digits);
    cowl_iri_release(xsd.iri.lang_range);

    cowl_class_release(owl.cls.thing);
    cowl_class_release(owl.cls.nothing);

    cowl_datatype_release(rdf.dt.plain_literal);
}

CowlOWLVocab* cowl_owl_vocab_get(void) {
    return &owl;
}

CowlRDFVocab* cowl_rdf_vocab_get(void) {
    return &rdf;
}

CowlXSDVocab* cowl_xsd_vocab_get(void) {
    return &xsd;
}
