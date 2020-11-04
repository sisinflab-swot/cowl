/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_id_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlString* cowl_ontology_id_to_string(CowlOntologyID id)
    COWL_TO_STRING_IMPL(ontology_id, id)

bool cowl_ontology_id_equals(CowlOntologyID lhs, CowlOntologyID rhs) {
    if (lhs.ontology_iri != rhs.ontology_iri &&
        !cowl_iri_equals(lhs.ontology_iri, rhs.ontology_iri)) {
        return false;
    }

    if (lhs.version_iri != rhs.version_iri &&
        !cowl_iri_equals(lhs.version_iri, rhs.version_iri)) {
        return false;
    }

    return true;
}

cowl_uint_t cowl_ontology_id_hash(CowlOntologyID id) {
    cowl_uint_t hash = COWL_HASH_INIT_ONTO_ID;

    if (id.ontology_iri) hash = cowl_hash_iter(hash, cowl_iri_hash(id.ontology_iri));
    if (id.version_iri) hash = cowl_hash_iter(hash, cowl_iri_hash(id.version_iri));

    return hash;
}
