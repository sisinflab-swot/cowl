/// @author Ivano Bilenchi

#include "cowl_obj_prop_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"

CowlIRI const* cowl_obj_prop_get_iri(CowlObjProp const *prop) {
    return prop->iri;
}

bool cowl_obj_prop_equals(CowlObjProp const *lhs, CowlObjProp const *rhs) {
    return cowl_iri_equals(lhs->iri, rhs->iri);
}

uint32_t cowl_obj_prop_hash(CowlObjProp const *prop) {
    return cowl_hash_1(COWL_HASH_INIT_OBJ_PROP, cowl_iri_hash(prop->iri));
}
