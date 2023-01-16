/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_id.h"
#include "cowl_iri.h"

bool cowl_ontology_id_equals(CowlOntologyId lhs, CowlOntologyId rhs) {
    if (lhs.iri != rhs.iri && !cowl_iri_equals(lhs.iri, rhs.iri)) return false;
    if (lhs.version != rhs.version && !cowl_iri_equals(lhs.version, rhs.version)) return false;
    return true;
}

ulib_uint cowl_ontology_id_hash(CowlOntologyId id) {
    if (id.iri) {
        ulib_uint hash = cowl_iri_hash(id.iri);
        if (id.version) hash = uhash_combine_hash(hash, cowl_iri_hash(id.version));
        return hash;
    }
    if (id.version) return cowl_iri_hash(id.version);
    return 0;
}
