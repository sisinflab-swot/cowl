/// @author Ivano Bilenchi

#include "cowl_anon_individual_private.h"
#include "cowl_hash_utils.h"
#include "cowl_string.h"

CowlString const* cowl_anon_individual_get_id(CowlAnonIndividual const *ind) {
    return ind->id;
}

bool cowl_anon_individual_equals(CowlAnonIndividual const *lhs, CowlAnonIndividual const *rhs) {
    return cowl_string_equals(lhs->id, rhs->id);
}

uint32_t cowl_anon_individual_hash(CowlAnonIndividual const *ind) {
    return cowl_hash_1(COWL_HASH_INIT_ANON_INDIVIDUAL, cowl_string_hash(ind->id));
}
