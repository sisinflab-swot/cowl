/// @author Ivano Bilenchi

#include "cowl_ontology_id_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

CowlIRI const* cowl_ontology_id_get_onto_iri(CowlOntologyId const *id) {
    return id->onto_iri;
}

CowlIRI const* cowl_ontology_id_get_version_iri(CowlOntologyId const *id) {
    return id->version_iri;
}

bool cowl_ontology_id_equals(CowlOntologyId const *lhs, CowlOntologyId const *rhs) {
    return cowl_iri_equals(lhs->onto_iri, rhs->onto_iri) &&
           cowl_iri_equals(lhs->version_iri, rhs->version_iri);
}

uint32_t cowl_ontology_id_hash(CowlOntologyId const *id) {
    return cowl_hash_2(COWL_HASH_INIT_ONTO_ID,
                       cowl_iri_hash(id->onto_iri),
                       cowl_iri_hash(id->version_iri));
}
