/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_rdfs_vocab_private.h"
#include "cowl_vocab_utils.h"

static CowlRDFSVocab vocab;

static inline cowl_ret cowl_rdfs_vocab_validate(void) {
    if (vocab.ns && vocab.iri.comment && vocab.iri.defined_by && vocab.iri.label &&
        vocab.iri.literal && vocab.iri.see_also && vocab.dt.literal && vocab.annot_prop.comment &&
        vocab.annot_prop.defined_by && vocab.annot_prop.label && vocab.annot_prop.see_also) {
        return COWL_OK;
    }
    return COWL_ERR_MEM;
}

cowl_ret cowl_rdfs_vocab_init(void) {
    CowlString *ns = cowl_string_vocab("http://www.w3.org/2000/01/rdf-schema#");

    CowlRDFSIRIVocab v = {
        .comment = cowl_iri_vocab(ns, "comment"),
        .defined_by = cowl_iri_vocab(ns, "isDefinedBy"),
        .label = cowl_iri_vocab(ns, "label"),
        .literal = cowl_iri_vocab(ns, "Literal"),
        .see_also = cowl_iri_vocab(ns, "seeAlso"),
    };

    vocab = (CowlRDFSVocab){
        .ns = ns,
        .iri = v,
        .dt = { .literal = cowl_datatype_vocab(v.literal) },
        .annot_prop = {
            .comment = cowl_annot_prop_vocab(v.comment),
            .defined_by = cowl_annot_prop_vocab(v.defined_by),
            .label = cowl_annot_prop_vocab(v.label),
            .see_also = cowl_annot_prop_vocab(v.see_also),
        },
    };

    return cowl_rdfs_vocab_validate();
}

void cowl_rdfs_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);

    cowl_iri_vocab_free(vocab.iri.comment);
    cowl_iri_vocab_free(vocab.iri.defined_by);
    cowl_iri_vocab_free(vocab.iri.label);
    cowl_iri_vocab_free(vocab.iri.literal);
    cowl_iri_vocab_free(vocab.iri.see_also);

    cowl_datatype_vocab_free(vocab.dt.literal);
    cowl_annot_prop_vocab_free(vocab.annot_prop.comment);
    cowl_annot_prop_vocab_free(vocab.annot_prop.defined_by);
    cowl_annot_prop_vocab_free(vocab.annot_prop.label);
    cowl_annot_prop_vocab_free(vocab.annot_prop.see_also);
}

CowlRDFSVocab const *cowl_rdfs_vocab(void) {
    return &vocab;
}
