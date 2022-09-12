/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_owl_vocab_private.h"
#include "cowl_vocab_utils.h"

static CowlOWLVocab vocab;

static inline cowl_ret cowl_owl_vocab_validate(void) {
    if (vocab.ns && vocab.iri.thing && vocab.iri.nothing && vocab.iri.top_obj_prop &&
        vocab.iri.bottom_obj_prop && vocab.iri.top_data_prop && vocab.iri.bottom_data_prop &&
        vocab.iri.backward_comp && vocab.iri.deprecated && vocab.iri.incompatible &&
        vocab.iri.prior_version && vocab.iri.rational && vocab.iri.real &&
        vocab.iri.version_info && vocab.cls.thing && vocab.cls.nothing &&
        vocab.dt.rational && vocab.dt.real && vocab.obj_prop.top_obj_prop &&
        vocab.obj_prop.bottom_obj_prop && vocab.data_prop.top_data_prop &&
        vocab.data_prop.bottom_data_prop && vocab.annot_prop.backward_comp &&
        vocab.annot_prop.deprecated && vocab.annot_prop.incompatible &&
        vocab.annot_prop.prior_version && vocab.annot_prop.version_info) {
        return COWL_OK;
    }
    return COWL_ERR_MEM;
}

cowl_ret cowl_owl_vocab_init(void) {
    CowlString *ns = cowl_string_vocab("http://www.w3.org/2002/07/owl#");

    CowlOWLIRIVocab v = {
        .thing = cowl_iri_vocab(ns, "Thing"),
        .nothing = cowl_iri_vocab(ns, "Nothing"),
        .top_obj_prop = cowl_iri_vocab(ns, "topObjectProperty"),
        .bottom_obj_prop = cowl_iri_vocab(ns, "bottomObjectProperty"),
        .top_data_prop = cowl_iri_vocab(ns, "topDataProperty"),
        .bottom_data_prop = cowl_iri_vocab(ns, "bottomDataProperty"),
        .backward_comp = cowl_iri_vocab(ns, "backwardCompatibleWith"),
        .deprecated = cowl_iri_vocab(ns, "deprecated"),
        .incompatible = cowl_iri_vocab(ns, "incompatibleWith"),
        .prior_version = cowl_iri_vocab(ns, "priorVersion"),
        .rational = cowl_iri_vocab(ns, "rational"),
        .real = cowl_iri_vocab(ns, "real"),
        .version_info = cowl_iri_vocab(ns, "versionInfo")
    };

    vocab = (struct CowlOWLVocab) {
        .ns = ns,
        .iri = v,

        .cls = {
            .thing = cowl_class_vocab(v.thing),
            .nothing = cowl_class_vocab(v.nothing)
        },

        .dt = {
            .rational = cowl_datatype_vocab(v.rational),
            .real = cowl_datatype_vocab(v.real)
        },

        .obj_prop = {
            .top_obj_prop = cowl_obj_prop_vocab(v.top_obj_prop),
            .bottom_obj_prop = cowl_obj_prop_vocab(v.bottom_obj_prop)
        },

        .data_prop = {
            .top_data_prop = cowl_data_prop_vocab(v.top_data_prop),
            .bottom_data_prop = cowl_data_prop_vocab(v.bottom_data_prop)
        },

        .annot_prop = {
            .backward_comp = cowl_annot_prop_vocab(v.backward_comp),
            .deprecated = cowl_annot_prop_vocab(v.deprecated),
            .incompatible = cowl_annot_prop_vocab(v.incompatible),
            .prior_version = cowl_annot_prop_vocab(v.prior_version),
            .version_info = cowl_annot_prop_vocab(v.version_info)
        }
    };

    return cowl_owl_vocab_validate();
}

void cowl_owl_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);

    cowl_iri_vocab_free(vocab.iri.thing);
    cowl_iri_vocab_free(vocab.iri.nothing);
    cowl_iri_vocab_free(vocab.iri.top_obj_prop);
    cowl_iri_vocab_free(vocab.iri.bottom_obj_prop);
    cowl_iri_vocab_free(vocab.iri.top_data_prop);
    cowl_iri_vocab_free(vocab.iri.bottom_data_prop);
    cowl_iri_vocab_free(vocab.iri.backward_comp);
    cowl_iri_vocab_free(vocab.iri.deprecated);
    cowl_iri_vocab_free(vocab.iri.incompatible);
    cowl_iri_vocab_free(vocab.iri.prior_version);
    cowl_iri_vocab_free(vocab.iri.rational);
    cowl_iri_vocab_free(vocab.iri.real);
    cowl_iri_vocab_free(vocab.iri.version_info);

    cowl_class_vocab_free(vocab.cls.thing);
    cowl_class_vocab_free(vocab.cls.nothing);

    cowl_datatype_vocab_free(vocab.dt.rational);
    cowl_datatype_vocab_free(vocab.dt.real);

    cowl_obj_prop_vocab_free(vocab.obj_prop.top_obj_prop);
    cowl_obj_prop_vocab_free(vocab.obj_prop.bottom_obj_prop);

    cowl_data_prop_vocab_free(vocab.data_prop.top_data_prop);
    cowl_data_prop_vocab_free(vocab.data_prop.bottom_data_prop);

    cowl_annot_prop_vocab_free(vocab.annot_prop.backward_comp);
    cowl_annot_prop_vocab_free(vocab.annot_prop.deprecated);
    cowl_annot_prop_vocab_free(vocab.annot_prop.incompatible);
    cowl_annot_prop_vocab_free(vocab.annot_prop.prior_version);
    cowl_annot_prop_vocab_free(vocab.annot_prop.version_info);
}

CowlOWLVocab const* cowl_owl_vocab(void) {
    return &vocab;
}
