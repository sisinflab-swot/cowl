/// @author Ivano Bilenchi

#include "cowl_individual_private.h"
#include "cowl_anon_ind.h"
#include "cowl_named_ind.h"

CowlIndividual* cowl_individual_retain(CowlIndividual *ind) {
    return cowl_object_retain(ind);
}

void cowl_individual_release(CowlIndividual *ind) {
    if (!ind) return;

    if (ind->is_named) {
        cowl_named_ind_release((CowlNamedInd *)ind);
    } else {
        cowl_anon_ind_release((CowlAnonInd *)ind);
    }
}

bool cowl_individual_is_named(CowlIndividual *ind) {
    return ind->is_named;
}

bool cowl_individual_equals(CowlIndividual *lhs, CowlIndividual *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_individual_hash(CowlIndividual *ind) {
    return uhash_ptr_hash(ind);
}

bool cowl_individual_iterate_signature(CowlIndividual *ind, void *ctx, CowlEntityIterator iter) {
    if (!ind->is_named) return true;
    return cowl_named_ind_iterate_signature((CowlNamedInd *)ind, ctx, iter);
}
