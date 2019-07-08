/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_owl_vocab_private.h"
#include "cowl_class.h"
#include "cowl_iri_private.h"
#include "cowl_string.h"

#define CS_OWL_NS "http://www.w3.org/2002/07/owl#"
#define CS_OWL_THING_REM "Thing"
#define CS_OWL_NOTHING_REM "Nothing"

static cowl_struct(CowlOWLVocab) vocab;

void cowl_owl_vocab_init(void) {
    CowlString *owl_ns_str = cowl_string_from_static(CS_OWL_NS);
    CowlString *owl_thing_str = cowl_string_from_static(CS_OWL_THING_REM);
    CowlString *owl_nothing_str = cowl_string_from_static(CS_OWL_NOTHING_REM);

    CowlIRI *owl_thing_iri = cowl_iri_get(owl_ns_str, owl_thing_str);
    CowlIRI *owl_nothing_iri = cowl_iri_get(owl_ns_str, owl_nothing_str);

    vocab = (cowl_struct(CowlOWLVocab)) {
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
}

void cowl_owl_vocab_deinit(void) {
    cowl_string_release(vocab.ns);

    cowl_iri_release(vocab.iri.thing);
    cowl_iri_release(vocab.iri.nothing);

    cowl_class_release(vocab.cls.thing);
    cowl_class_release(vocab.cls.nothing);
}

CowlOWLVocab* cowl_owl_vocab_get(void) {
    return &vocab;
}
