/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_vocab.h"
#include "cowl_owl_vocab_private.h"
#include "cowl_rdf_vocab_private.h"
#include "cowl_rdfs_vocab_private.h"
#include "cowl_string_private.h"
#include "cowl_xsd_vocab_private.h"

static CowlVocab vocab;

CowlVocab const *cowl_vocab(void) {
    return &vocab;
}

cowl_ret cowl_vocab_init(void) {
    if (cowl_owl_vocab_init() || cowl_rdf_vocab_init() || cowl_rdfs_vocab_init() ||
        cowl_xsd_vocab_init())
        return COWL_ERR_MEM;
    vocab.owl = cowl_owl_vocab();
    vocab.rdf = cowl_rdf_vocab();
    vocab.rdfs = cowl_rdfs_vocab();
    vocab.xsd = cowl_xsd_vocab();
    return COWL_OK;
}

void cowl_vocab_deinit(void) {
    cowl_owl_vocab_deinit();
    cowl_rdf_vocab_deinit();
    cowl_rdfs_vocab_deinit();
    cowl_xsd_vocab_deinit();
}

bool cowl_vocab_is_reserved_prefix(CowlString *prefix) {
    return cowl_string_equals(prefix, cowl_owl_vocab()->prefix) ||
           cowl_string_equals(prefix, cowl_rdf_vocab()->prefix) ||
           cowl_string_equals(prefix, cowl_rdfs_vocab()->prefix) ||
           cowl_string_equals(prefix, cowl_xsd_vocab()->prefix);
}

bool cowl_vocab_is_reserved_ns(CowlString *ns) {
    return cowl_string_equals(ns, cowl_owl_vocab()->ns) ||
           cowl_string_equals(ns, cowl_rdf_vocab()->ns) ||
           cowl_string_equals(ns, cowl_rdfs_vocab()->ns) ||
           cowl_string_equals(ns, cowl_xsd_vocab()->ns);
}

bool cowl_vocab_is_reserved_prefix_raw(UString prefix) {
    return ustring_equals(prefix, cowl_owl_vocab()->prefix->raw_string) ||
           ustring_equals(prefix, cowl_rdf_vocab()->prefix->raw_string) ||
           ustring_equals(prefix, cowl_rdfs_vocab()->prefix->raw_string) ||
           ustring_equals(prefix, cowl_xsd_vocab()->prefix->raw_string);
}

bool cowl_vocab_is_reserved_ns_raw(UString ns) {
    return ustring_equals(ns, cowl_owl_vocab()->ns->raw_string) ||
           ustring_equals(ns, cowl_rdf_vocab()->ns->raw_string) ||
           ustring_equals(ns, cowl_rdfs_vocab()->ns->raw_string) ||
           ustring_equals(ns, cowl_xsd_vocab()->ns->raw_string);
}
