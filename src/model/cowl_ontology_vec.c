/// @author Ivano Bilenchi

#include "cowl_ontology_vec.h"
#include "cowl_ontology.h"

VECTOR_IMPL_EQUATABLE(CowlOntologyPtr, cowl_ontology_equals)

void cowl_ontology_vec_push(CowlMutableOntologyVec *vec, CowlOntology *onto) {
    cowl_ontology_retain(onto);
    vector_push(CowlOntologyPtr, vec, onto);
}

void cowl_ontology_vec_free(CowlMutableOntologyVec *vec) {
    vector_deep_free(CowlOntologyPtr, vec, cowl_ontology_release);
}
