/// @author Ivano Bilenchi

#include "cowl_literal_set.h"
#include "cowl_literal.h"

UHASH_SET_IMPL(CowlLiteralSet, CowlLiteral*, cowl_literal_hash, cowl_literal_equals)

void cowl_literal_set_free(CowlLiteralSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlLiteralSet, set, literal, cowl_literal_release(literal));
    uhash_free(CowlLiteralSet, (UHash(CowlLiteralSet) *)set);
}

bool cowl_literal_set_equals(CowlLiteralSet *lhs, CowlLiteralSet *rhs) {
    return uhset_equals(CowlLiteralSet, lhs, rhs);
}

cowl_uint_t cowl_literal_set_hash(CowlLiteralSet *set) {
    return uhset_hash(CowlLiteralSet, set);
}

bool cowl_literal_set_iterate_signature(CowlLiteralSet *set, CowlEntityIterator *iter) {
    uhash_foreach_key(CowlLiteralSet, set, literal, {
        if (!cowl_literal_iterate_signature(literal, iter)) return false;
    });
    return true;
}
