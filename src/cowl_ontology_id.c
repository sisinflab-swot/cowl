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
#include "cowl_primitive_private.h"
#include "ulib.h"

bool cowl_ontology_id_equals(CowlOntologyId lhs, CowlOntologyId rhs) {
    if (lhs.iri != rhs.iri && !cowl_primitive_equals(lhs.iri, rhs.iri)) return false;
    if (lhs.version != rhs.version && !cowl_primitive_equals(lhs.version, rhs.version))
        return false;
    return true;
}

ulib_uint cowl_ontology_id_hash(CowlOntologyId id) {
    if (id.iri) {
        ulib_uint hash = cowl_primitive_hash(id.iri);
        if (id.version) hash = ulib_hash_combine(hash, cowl_primitive_hash(id.version));
        return hash;
    }
    if (id.version) return cowl_primitive_hash(id.version);
    return 0;
}
