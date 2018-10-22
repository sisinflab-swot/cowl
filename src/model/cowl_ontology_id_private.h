/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_ID_PRIVATE_H
#define COWL_ONTOLOGY_ID_PRIVATE_H

#include "cowl_ontology_id.h"

COWL_BEGIN_DECLS

typedef struct CowlOntologyId {
    CowlIRI const *onto_iri;
    CowlIRI const *version_iri;
} CowlOntologyId;

CowlOntologyId* cowl_ontology_id_alloc(CowlIRI const *onto_iri, CowlIRI const *version_iri);
void cowl_ontology_id_free(CowlOntologyId const *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_PRIVATE_H
