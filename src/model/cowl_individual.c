/// @author Ivano Bilenchi

#include "cowl_individual_private.h"
#include "cowl_anon_individual.h"
#include "cowl_named_individual.h"

CowlIndividual* cowl_individual_retain(CowlIndividual *ind) {
    return cowl_individual_ref_incr(ind);
}

void cowl_individual_release(CowlIndividual *ind) {
    if (!ind) return;

    if (ind->is_named) {
        cowl_named_individual_release((CowlNamedIndividual *)ind);
    } else {
        cowl_anon_individual_release((CowlAnonIndividual *)ind);
    }
}

bool cowl_individual_is_named(CowlIndividual *ind) {
    return ind->is_named;
}

bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs) {
    if (lhs->is_named != rhs->is_named) return false;

    if (lhs->is_named) {
        return cowl_named_individual_equals((CowlNamedIndividual *)lhs, (CowlNamedIndividual *)rhs);
    } else {
        return cowl_anon_individual_equals((CowlAnonIndividual *)lhs, (CowlAnonIndividual *)rhs);
    }
}

uint32_t cowl_individual_hash(CowlIndividual *ind) {
    if (ind->is_named) {
        return cowl_named_individual_hash((CowlNamedIndividual *)ind);
    } else {
        return cowl_anon_individual_hash((CowlAnonIndividual *)ind);
    }
}

bool cowl_individual_iterate_signature(CowlIndividual *ind, void *ctx, CowlEntityIterator iter) {
    if (!ind->is_named) return true;
    return cowl_named_individual_iterate_signature((CowlNamedIndividual *)ind, ctx, iter);
}
