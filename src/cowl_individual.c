/// @author Ivano Bilenchi

#include "cowl_individual_private.h"
#include <assert.h>

bool cowl_individual_is_named(CowlIndividual const *individual) {
    return individual->is_named;
}

CowlEntity const* cowl_individual_named(CowlIndividual const *individual) {
    assert(individual->is_named);
    return individual->named;
}

CowlString const* cowl_individual_anonymous_id(CowlIndividual const *individual) {
    assert(!individual->is_named);
    return individual->anonymous_id;
}
