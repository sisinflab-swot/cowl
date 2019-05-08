/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_ID_PRIVATE_H
#define COWL_ONTOLOGY_ID_PRIVATE_H

#include "cowl_ontology_id.h"

COWL_BEGIN_DECLS

cowl_struct(CowlOntologyId) {
    CowlIRI *onto_iri;
    CowlIRI *version_iri;
};

CowlOntologyId* cowl_ontology_id_alloc(CowlIRI *onto_iri, CowlIRI *version_iri);
void cowl_ontology_id_free(CowlOntologyId *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_PRIVATE_H
