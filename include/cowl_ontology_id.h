/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_ID_H
#define COWL_ONTOLOGY_ID_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlOntologyID);

CowlIRI* cowl_ontology_id_get_onto_iri(CowlOntologyID *id);
CowlIRI* cowl_ontology_id_get_version_iri(CowlOntologyID *id);

bool cowl_ontology_id_equals(CowlOntologyID *lhs, CowlOntologyID *rhs);
cowl_uint_t cowl_ontology_id_hash(CowlOntologyID *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_H
