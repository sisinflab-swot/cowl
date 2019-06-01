/// @author Ivano Bilenchi

#include "cowl_literal_set_private.h"
#include "cowl_literal.h"

UHASH_SET_IMPL(CowlLiteralSet, CowlLiteral*, cowl_literal_hash, cowl_literal_equals)

bool cowl_literal_set_insert(CowlMutableLiteralSet *set, CowlLiteral *literal) {
    return uhset_insert(CowlLiteralSet, set, cowl_literal_retain(literal)) == UHASH_INSERTED;
}

void cowl_literal_set_free(CowlLiteralSet *set) {
    if (!set) return;
    uhash_foreach_key(CowlLiteralSet, set, literal, cowl_literal_release(literal));
    uhash_free(CowlLiteralSet, (UHash(CowlLiteralSet) *)set);
}
