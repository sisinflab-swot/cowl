/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_rdf_vocab_private.h"
#include "cowl_vocab_private.h"

static CowlRDFVocab vocab;

static inline cowl_ret cowl_rdf_vocab_validate(void) {
    if (!(vocab.ns && vocab.prefix)) return COWL_ERR_MEM;

    void **temp = (void **)&vocab.iri;
    size_t count = sizeof(vocab.iri) / sizeof(void *);
    for (size_t i = 0; i < count; ++i) {
        if (!temp[i]) return COWL_ERR_MEM;
    }

    temp = (void **)&vocab.dt;
    count = sizeof(vocab.dt) / sizeof(void *);
    for (size_t i = 0; i < count; ++i) {
        if (!temp[i]) return COWL_ERR_MEM;
    }

    return COWL_OK;
}

cowl_ret cowl_rdf_vocab_init(void) {
    CowlString *ns = cowl_string_vocab_intern("http://www.w3.org/1999/02/22-rdf-syntax-ns#");

    CowlRDFIRIVocab v = {
        .lang_range = cowl_iri_vocab(ns, "langRange"),
        .lang_string = cowl_iri_vocab(ns, "langString"),
        .plain_literal = cowl_iri_vocab(ns, "PlainLiteral"),
        .xml_literal = cowl_iri_vocab(ns, "XMLLiteral"),
    };

    vocab = (struct CowlRDFVocab){
        .ns = ns,
        .prefix = cowl_string_vocab("rdf"),
        .iri = v,
        .dt = {
            .lang_string = cowl_datatype_vocab(v.lang_string),
            .plain_literal = cowl_datatype_vocab(v.plain_literal),
            .xml_literal = cowl_datatype_vocab(v.xml_literal),
        },
    };

    return cowl_rdf_vocab_validate();
}

void cowl_rdf_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);
    cowl_string_vocab_free(vocab.prefix);

    CowlIRI **iris = (CowlIRI **)&vocab.iri;
    size_t count = sizeof(vocab.iri) / sizeof(CowlIRI *);
    for (size_t i = 0; i < count; ++i) {
        cowl_iri_vocab_free(iris[i]);
    }

    CowlDatatype **dts = (CowlDatatype **)&vocab.dt;
    count = sizeof(vocab.dt) / sizeof(CowlDatatype *);
    for (size_t i = 0; i < count; ++i) {
        cowl_datatype_vocab_free(dts[i]);
    }
}

CowlRDFVocab const *cowl_rdf_vocab(void) {
    return &vocab;
}
