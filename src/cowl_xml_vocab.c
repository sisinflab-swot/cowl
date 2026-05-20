/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_xml_vocab.h"
#include "cowl_ret.h"
#include "cowl_vocab_private.h"
#include "cowl_xml_vocab_private.h"
#include "ulib.h"

static CowlXMLVocab vocab;

static inline cowl_ret cowl_xml_vocab_validate(void) {
    if (vocab.ns && vocab.prefix && vocab.xmlns_ns && vocab.xmlns_prefix) return COWL_OK;
    return COWL_ERR_MEM;
}

cowl_ret cowl_xml_vocab_init(void) {
    vocab = (struct CowlXMLVocab){
        .ns = cowl_string_vocab_intern("http://www.w3.org/XML/1998/namespace"),
        .prefix = cowl_string_vocab("xml"),
        .xmlns_ns = cowl_string_vocab_intern("http://www.w3.org/2000/xmlns/"),
        .xmlns_prefix = cowl_string_vocab("xmlns"),
    };

    cowl_ret const ret = cowl_xml_vocab_validate();
    if (cowl_is_err(ret)) cowl_xml_vocab_deinit();
    return ret;
}

void cowl_xml_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);
    cowl_string_vocab_free(vocab.prefix);
    cowl_string_vocab_free(vocab.xmlns_ns);
    cowl_string_vocab_free(vocab.xmlns_prefix);
    vocab = (CowlXMLVocab)ulib_zero_init;
}

CowlXMLVocab const *cowl_xml_vocab(void) {
    return &vocab;
}
