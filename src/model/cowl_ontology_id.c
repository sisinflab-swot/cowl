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
#include "cowl_alloc.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlOntologyID* cowl_ontology_id_alloc(CowlIRI *onto_iri, CowlIRI *version_iri) {
    CowlOntologyID *id = cowl_alloc(id);
    if (!id) return NULL;

    *id = (CowlOntologyID) {
        .onto_iri = onto_iri ? cowl_iri_retain(onto_iri) : NULL,
        .version_iri = version_iri ? cowl_iri_retain(version_iri) : NULL
    };

    return id;
}

CowlOntologyID* cowl_ontology_id_alloc_anonymous(void) {
    return cowl_ontology_id_alloc(NULL, NULL);
}

void cowl_ontology_id_free(CowlOntologyID *id) {
    if (!id) return;
    cowl_iri_release(id->onto_iri);
    cowl_iri_release(id->version_iri);
    cowl_free(id);
}

CowlIRI* cowl_ontology_id_get_onto_iri(CowlOntologyID *id) {
    return id->onto_iri;
}

CowlIRI* cowl_ontology_id_get_version_iri(CowlOntologyID *id) {
    return id->version_iri;
}

CowlString* cowl_ontology_id_to_string(CowlOntologyID *id)
    COWL_TO_STRING_IMPL(ontology_id, id)

bool cowl_ontology_id_equals(CowlOntologyID *lhs, CowlOntologyID *rhs) {
    if (lhs == rhs) return true;

    // If either of the ontology IRIs are NULL, then we assume the IDs are not equal.
    // In fact, if they are both NULL, then the IDs are anonymous and they didn't pass
    // the pointer equality test. If only one of them is NULL, then one of the IDs is
    // anonymous, while the other is named.
    if (!(lhs->onto_iri && rhs->onto_iri)) return false;

    return cowl_iri_equals(lhs->onto_iri, rhs->onto_iri) &&
           cowl_iri_equals(lhs->version_iri, rhs->version_iri);
}

cowl_uint_t cowl_ontology_id_hash(CowlOntologyID *id) {
    if (!id->onto_iri) return uhash_ptr_hash(id);
    return cowl_hash_2(COWL_HASH_INIT_ONTO_ID,
                       cowl_iri_hash(id->onto_iri),
                       cowl_iri_hash(id->version_iri));
}
