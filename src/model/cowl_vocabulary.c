/// @author Ivano Bilenchi

#include "cowl_vocabulary_private.h"
#include "cowl_class.h"
#include "cowl_iri.h"
#include "cowl_string.h"

#define COWL_STR_OWL_NS "http://www.w3.org/2002/07/owl#"
#define COWL_STR_OWL_THING_REM "Thing"
#define COWL_STR_OWL_NOTHING_REM "Nothing"

static cowl_struct(CowlVocabulary) cowl_vocabulary;

void cowl_vocabulary_init(void) {
    CowlString *owl_ns_str = cowl_string_from_static(COWL_STR_OWL_NS);
    CowlString *owl_thing_rem_str = cowl_string_from_static(COWL_STR_OWL_THING_REM);
    CowlString *owl_nothing_rem_str = cowl_string_from_static(COWL_STR_OWL_NOTHING_REM);

    CowlIRI *owl_thing_iri = cowl_iri_get(owl_ns_str, owl_thing_rem_str);
    CowlIRI *owl_nothing_iri = cowl_iri_get(owl_ns_str, owl_nothing_rem_str);

    CowlClass *owl_thing = cowl_class_get(owl_thing_iri);
    CowlClass *owl_nothing = cowl_class_get(owl_nothing_iri);

    cowl_vocabulary = (cowl_struct(CowlVocabulary)) {
        .ns = {
            .owl = owl_ns_str
        },

        .rem = {
            .thing = owl_thing_rem_str,
            .nothing = owl_nothing_rem_str
        },

        .iri = {
            .thing = owl_thing_iri,
            .nothing = owl_nothing_iri
        },

        .cls = {
            .thing = owl_thing,
            .nothing = owl_nothing
        }
    };
}

void cowl_vocabulary_deinit(void) {
    cowl_string_release(cowl_vocabulary.ns.owl);
    cowl_string_release(cowl_vocabulary.rem.thing);
    cowl_string_release(cowl_vocabulary.rem.nothing);
    cowl_iri_release(cowl_vocabulary.iri.thing);
    cowl_iri_release(cowl_vocabulary.iri.nothing);
    cowl_class_release(cowl_vocabulary.cls.thing);
    cowl_class_release(cowl_vocabulary.cls.nothing);
}

CowlVocabulary* cowl_vocabulary_get(void) {
    return &cowl_vocabulary;
}

void cowl_vocabulary_iterate_signature(void *ctx, CowlEntityIterator iter) {
    iter(ctx, cowl_entity_wrap_class(cowl_vocabulary.cls.thing));
    iter(ctx, cowl_entity_wrap_class(cowl_vocabulary.cls.nothing));
}
