/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_rdf_vocab_private.h"
#include "cowl_datatype.h"
#include "cowl_iri_private.h"
#include "cowl_string.h"

#define CS_RDF_NS "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define CS_RDF_PLAIN_LITERAL_REM "PlainLiteral"

static cowl_struct(CowlRDFVocab) vocab;

void cowl_rdf_vocab_init(void) {
    CowlString *rdf_ns_str = cowl_string_from_static(CS_RDF_NS);
    CowlString *rdf_plain_literal_str = cowl_string_from_static(CS_RDF_PLAIN_LITERAL_REM);

    CowlIRI *rdf_plain_literal_iri = cowl_iri_get(rdf_ns_str, rdf_plain_literal_str);

    vocab = (cowl_struct(CowlRDFVocab)) {
        .ns = rdf_ns_str,

        .iri = {
            .plain_literal = rdf_plain_literal_iri
        },

        .dt = {
            .plain_literal = cowl_datatype_get(rdf_plain_literal_iri)
        }
    };
}

void cowl_rdf_vocab_deinit(void) {
    cowl_string_release(vocab.ns);
    cowl_iri_release(vocab.iri.plain_literal);
    cowl_datatype_release(vocab.dt.plain_literal);
}

CowlRDFVocab* cowl_rdf_vocab_get(void) {
    return &vocab;
}
