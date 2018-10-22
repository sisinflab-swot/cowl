/// @author Ivano Bilenchi

#include "cowl_ontology_id_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

#pragma mark - Private

CowlOntologyId* cowl_ontology_id_alloc(CowlIRI const *onto_iri, CowlIRI const *version_iri) {
    CowlOntologyId init = {
        .onto_iri = cowl_iri_retain(onto_iri),
        .version_iri = cowl_iri_retain(version_iri)
    };

    CowlOntologyId *id = malloc(sizeof(*id));
    memcpy(id, &init, sizeof(*id));
    return id;
}

void cowl_ontology_id_free(CowlOntologyId const *id) {
    if (!id) return;
    cowl_iri_release(id->onto_iri);
    cowl_iri_release(id->version_iri);
    free((void *)id);
}

#pragma mark - Public

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
