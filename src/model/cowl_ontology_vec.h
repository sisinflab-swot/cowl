/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_VEC_H
#define COWL_ONTOLOGY_VEC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlOntology);
typedef CowlOntology* CowlOntologyPtr;

VECTOR_DECL_EQUATABLE(CowlOntologyPtr)
cowl_vector_decl(CowlOntologyPtr, CowlOntologyVec);

void cowl_ontology_vec_free(Vector(CowlOntologyPtr) *vec);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_VEC_H
