/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_id.h"
#include "cowl_iri.h"

bool cowl_ontology_id_equals(CowlOntologyId lhs, CowlOntologyId rhs) {
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

ulib_uint cowl_ontology_id_hash(CowlOntologyId id) {
    ulib_uint hash = 0, h;

    if (id.ontology_iri) {
        h = cowl_iri_hash(id.ontology_iri);
        hash = uhash_combine_hash(hash, h);
    }

    if (id.version_iri) {
        h = cowl_iri_hash(id.version_iri);
        hash = uhash_combine_hash(hash, h);
    }

    return hash;
}
