/// @author Ivano Bilenchi

#include "cowl_vocabulary_private.h"
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

static cowl_struct(CowlVocabulary) cowl_vocabulary;

void cowl_vocabulary_init(void) {
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

    cowl_vocabulary = (cowl_struct(CowlVocabulary)) {

        .ns = {
            .owl = owl_ns_str,
            .rdf = rdf_ns_str,
            .xsd = xsd_ns_str
        },

        .iri = {
            .thing = owl_thing_iri,
            .nothing = owl_nothing_iri,
            .rdf_plain_literal = rdf_plain_literal_iri,
            .xsd_length = cowl_iri_get(xsd_ns_str, xsd_length_str),
            .xsd_min_length = cowl_iri_get(xsd_ns_str, xsd_min_length_str),
            .xsd_max_length = cowl_iri_get(xsd_ns_str, xsd_max_length_str),
            .xsd_pattern = cowl_iri_get(xsd_ns_str, xsd_pattern_str),
            .xsd_min_inclusive = cowl_iri_get(xsd_ns_str, xsd_min_inclusive_str),
            .xsd_min_exclusive = cowl_iri_get(xsd_ns_str, xsd_min_exclusive_str),
            .xsd_max_inclusive = cowl_iri_get(xsd_ns_str, xsd_max_inclusive_str),
            .xsd_max_exclusive = cowl_iri_get(xsd_ns_str, xsd_max_exclusive_str),
            .xsd_total_digits = cowl_iri_get(xsd_ns_str, xsd_total_digits_str),
            .xsd_fraction_digits = cowl_iri_get(xsd_ns_str, xsd_fraction_digits_str),
            .xsd_lang_range = cowl_iri_get(xsd_ns_str, xsd_lang_range_str)
        },

        .cls = {
            .thing = cowl_class_get(owl_thing_iri),
            .nothing = cowl_class_get(owl_nothing_iri)
        },

        .dt = {
            .rdf_plain_literal = cowl_datatype_get(rdf_plain_literal_iri)
        }
    };
}

void cowl_vocabulary_deinit(void) {
    cowl_string_release(cowl_vocabulary.ns.owl);
    cowl_string_release(cowl_vocabulary.ns.rdf);
    cowl_iri_release(cowl_vocabulary.iri.thing);
    cowl_iri_release(cowl_vocabulary.iri.nothing);
    cowl_iri_release(cowl_vocabulary.iri.xsd_length);
    cowl_iri_release(cowl_vocabulary.iri.xsd_min_length);
    cowl_iri_release(cowl_vocabulary.iri.xsd_max_length);
    cowl_iri_release(cowl_vocabulary.iri.xsd_pattern);
    cowl_iri_release(cowl_vocabulary.iri.xsd_min_inclusive);
    cowl_iri_release(cowl_vocabulary.iri.xsd_min_exclusive);
    cowl_iri_release(cowl_vocabulary.iri.xsd_max_inclusive);
    cowl_iri_release(cowl_vocabulary.iri.xsd_max_exclusive);
    cowl_iri_release(cowl_vocabulary.iri.xsd_total_digits);
    cowl_iri_release(cowl_vocabulary.iri.xsd_fraction_digits);
    cowl_iri_release(cowl_vocabulary.iri.xsd_lang_range);
    cowl_iri_release(cowl_vocabulary.iri.rdf_plain_literal);
    cowl_class_release(cowl_vocabulary.cls.thing);
    cowl_class_release(cowl_vocabulary.cls.nothing);
    cowl_datatype_release(cowl_vocabulary.dt.rdf_plain_literal);
}

CowlVocabulary* cowl_vocabulary_get(void) {
    return &cowl_vocabulary;
}

void cowl_vocabulary_iterate_signature(CowlEntityIterator *iter) {
    cowl_iterate(iter, cowl_entity_wrap_class(cowl_vocabulary.cls.thing));
    cowl_iterate(iter, cowl_entity_wrap_class(cowl_vocabulary.cls.nothing));
    cowl_iterate(iter, cowl_entity_wrap_datatype(cowl_vocabulary.dt.rdf_plain_literal));
}
