/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_ID_PRIVATE_H
#define COWL_ONTOLOGY_ID_PRIVATE_H

#include "cowl_ontology_id.h"

COWL_BEGIN_DECLS

typedef struct CowlOntologyId {
    CowlIRI const *onto_iri;
    CowlIRI const *version_iri;
} CowlOntologyId;

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_PRIVATE_H
