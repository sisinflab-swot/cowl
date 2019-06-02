/// @author Ivano Bilenchi

#include "cowl_facet_restr_private.h"
#include "cowl_hash_utils.h"
#include "cowl_literal.h"

static CowlFacetRestr* cowl_facet_restr_alloc(CowlFacet facet, CowlLiteral *value) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_FACET_RESTR, facet, cowl_literal_hash(value));

    CowlFacetRestr init = {
        .super = COWL_OBJECT_INIT(hash),
        .facet = facet,
        .value = cowl_literal_retain(value)
    };

    cowl_struct(CowlFacetRestr) *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_facet_restr_free(CowlFacetRestr *restr) {
    if (!restr) return;
    cowl_literal_release(restr->value);
    free((void *)restr);
}

CowlFacetRestr* cowl_facet_restr_get(CowlFacet facet, CowlLiteral *value) {
    return cowl_facet_restr_alloc(facet, value);
}

CowlFacetRestr* cowl_facet_restr_retain(CowlFacetRestr *restr) {
    return cowl_object_retain(restr);
}

void cowl_facet_restr_release(CowlFacetRestr *restr) {
    if (restr && !cowl_object_release(restr)) {
        cowl_facet_restr_free(restr);
    }
}

CowlFacet cowl_facet_restr_get_facet(CowlFacetRestr *restr) {
    return restr->facet;
}

CowlLiteral* cowl_facet_restr_get_value(CowlFacetRestr *restr) {
    return restr->value;
}

bool cowl_facet_restr_equals(CowlFacetRestr *lhs, CowlFacetRestr *rhs) {
    return lhs->facet == rhs->facet && cowl_literal_equals(lhs->value, rhs->value);
}

cowl_uint_t cowl_facet_restr_hash(CowlFacetRestr *restr) {
    return cowl_object_hash_get(restr);
}

bool cowl_facet_restr_iterate_signature(CowlFacetRestr *restr, void *ctx, CowlEntityIterator iter) {
    return cowl_literal_iterate_signature(restr->value, ctx, iter);
}
