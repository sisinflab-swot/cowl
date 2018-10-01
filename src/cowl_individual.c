/// @author Ivano Bilenchi

#include "cowl_individual_private.h"
#include "cowl_anon_individual.h"
#include "cowl_named_individual.h"

bool cowl_individual_is_named(CowlIndividual const *ind) {
    return ind->is_named;
}

bool cowl_individual_equals(CowlIndividual const *lhs, CowlIndividual const *rhs) {
    if (lhs->is_named != rhs->is_named) return false;

    if (lhs->is_named) {
        return cowl_named_individual_equals((CowlNamedIndividual *)lhs,
                                            (CowlNamedIndividual *)rhs);
    } else {
        return cowl_anon_individual_equals((CowlAnonIndividual *)lhs,
                                           (CowlAnonIndividual *)rhs);
    }
}

uint32_t cowl_individual_hash(CowlIndividual const *ind) {
    if (ind->is_named) {
        return cowl_named_individual_hash((CowlNamedIndividual *)ind);
    } else {
        return cowl_anon_individual_hash((CowlAnonIndividual *)ind);
    }
}
