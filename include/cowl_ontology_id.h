/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_ID_H
#define COWL_ONTOLOGY_ID_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI CowlIRI;

typedef struct CowlOntologyId CowlOntologyId;

CowlIRI const* cowl_ontology_id_get_onto_iri(CowlOntologyId const *id);
CowlIRI const* cowl_ontology_id_get_version_iri(CowlOntologyId const *id);

bool cowl_ontology_id_equals(CowlOntologyId const *lhs, CowlOntologyId const *rhs);
uint32_t cowl_ontology_id_hash(CowlOntologyId const *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_H
