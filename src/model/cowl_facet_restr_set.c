/// @author Ivano Bilenchi

#include "cowl_facet_restr_set_private.h"
#include "cowl_facet_restr.h"

UHASH_SET_IMPL(CowlFacetRestrSet, CowlFacetRestr*, cowl_facet_restr_hash, cowl_facet_restr_equals)

bool cowl_facet_restr_set_insert(CowlMutableFacetRestrSet *set, CowlFacetRestr *restr) {
    return uhset_insert(CowlFacetRestrSet, set, cowl_facet_restr_retain(restr)) == UHASH_INSERTED;
}

void cowl_facet_restr_set_free(CowlFacetRestrSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlFacetRestrSet, set, restr, cowl_facet_restr_release(restr));
    uhash_free(CowlFacetRestrSet, (UHash(CowlFacetRestrSet) *)set);
}

bool cowl_facet_restr_set_equals(CowlFacetRestrSet *lhs, CowlFacetRestrSet *rhs) {
    return uhset_equals(CowlFacetRestrSet, lhs, rhs);
}

cowl_uint_t cowl_facet_restr_set_hash(CowlFacetRestrSet *set) {
    return uhset_hash(CowlFacetRestrSet, set);
}

bool cowl_facet_restr_set_iterate_signature(CowlFacetRestrSet *set, void *ctx,
                                            CowlEntityIterator iter) {
    uhash_foreach_key(CowlFacetRestrSet, set, restr, {
        if (!cowl_facet_restr_iterate_signature(restr, ctx, iter)) return false;
    });
    return true;
}
