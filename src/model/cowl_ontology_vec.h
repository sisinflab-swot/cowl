/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_VEC_H
#define COWL_ONTOLOGY_VEC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlOntology);
typedef CowlOntology* CowlOntologyPtr;

VECTOR_DECL_EQUATABLE(CowlOntologyPtr)
cowl_vector_decl(CowlOntologyPtr, CowlOntologyVec);
cowl_vector_decl_mutable(CowlOntologyPtr, CowlMutableOntologyVec);

void cowl_ontology_vec_push(CowlMutableOntologyVec *vec, CowlOntology *onto);
void cowl_ontology_vec_free(CowlMutableOntologyVec *vec);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_VEC_H
