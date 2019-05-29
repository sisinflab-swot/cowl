/// @author Ivano Bilenchi

#include "cowl_vocabulary_private.h"
#include "cowl_class.h"
#include "cowl_datatype.h"
#include "cowl_iri.h"
#include "cowl_string.h"

#define COWL_STR_OWL_NS "http://www.w3.org/2002/07/owl#"
#define COWL_STR_RDF_NS "http://www.w3.org/1999/02/22-rdf-syntax-ns#"

#define COWL_STR_OWL_THING_REM "Thing"
#define COWL_STR_OWL_NOTHING_REM "Nothing"
#define COWL_STR_RDF_PLAIN_LITERAL_REM "PlainLiteral"

static cowl_struct(CowlVocabulary) cowl_vocabulary;

void cowl_vocabulary_init(void) {
    CowlString *owl_ns_str = cowl_string_from_static(COWL_STR_OWL_NS);
    CowlString *rdf_ns_str = cowl_string_from_static(COWL_STR_RDF_NS);

    CowlString *owl_thing_rem_str = cowl_string_from_static(COWL_STR_OWL_THING_REM);
    CowlString *owl_nothing_rem_str = cowl_string_from_static(COWL_STR_OWL_NOTHING_REM);
    CowlString *rdf_plain_literal_rem_str = cowl_string_from_static(COWL_STR_RDF_PLAIN_LITERAL_REM);

    CowlIRI *owl_thing_iri = cowl_iri_get(owl_ns_str, owl_thing_rem_str);
    CowlIRI *owl_nothing_iri = cowl_iri_get(owl_ns_str, owl_nothing_rem_str);
    CowlIRI *rdf_plain_literal_iri = cowl_iri_get(rdf_ns_str, rdf_plain_literal_rem_str);

    cowl_vocabulary = (cowl_struct(CowlVocabulary)) {
        .ns = {
            .owl = owl_ns_str,
            .rdf = rdf_ns_str
        },

        .rem = {
            .thing = owl_thing_rem_str,
            .nothing = owl_nothing_rem_str,
            .plain_literal = rdf_plain_literal_rem_str
        },

        .iri = {
            .thing = owl_thing_iri,
            .nothing = owl_nothing_iri,
            .plain_literal = rdf_plain_literal_iri
        },

        .cls = {
            .thing = cowl_class_get(owl_thing_iri),
            .nothing = cowl_class_get(owl_nothing_iri)
        },

        .dt = {
            .plain_literal = cowl_datatype_get(rdf_plain_literal_iri)
        }
    };
}

void cowl_vocabulary_deinit(void) {
    cowl_string_release(cowl_vocabulary.ns.owl);
    cowl_string_release(cowl_vocabulary.ns.rdf);
    cowl_string_release(cowl_vocabulary.rem.thing);
    cowl_string_release(cowl_vocabulary.rem.nothing);
    cowl_string_release(cowl_vocabulary.rem.plain_literal);
    cowl_iri_release(cowl_vocabulary.iri.thing);
    cowl_iri_release(cowl_vocabulary.iri.nothing);
    cowl_iri_release(cowl_vocabulary.iri.plain_literal);
    cowl_class_release(cowl_vocabulary.cls.thing);
    cowl_class_release(cowl_vocabulary.cls.nothing);
    cowl_datatype_release(cowl_vocabulary.dt.plain_literal);
}

CowlVocabulary* cowl_vocabulary_get(void) {
    return &cowl_vocabulary;
}

void cowl_vocabulary_iterate_signature(void *ctx, CowlEntityIterator iter) {
    iter(ctx, cowl_entity_wrap_class(cowl_vocabulary.cls.thing));
    iter(ctx, cowl_entity_wrap_class(cowl_vocabulary.cls.nothing));
    iter(ctx, cowl_entity_wrap_datatype(cowl_vocabulary.dt.plain_literal));
}
