/// @author Ivano Bilenchi

#include "cowl_datatype_restr_private.h"
#include "cowl_facet_restr.h"
#include "cowl_facet_restr_set.h"
#include "cowl_datatype.h"
#include "cowl_hash_utils.h"

static CowlDatatypeRestr* cowl_datatype_restr_alloc(CowlDatatype *datatype,
                                                    CowlFacetRestrSet *restrictions) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATA_RESTR,
                                   cowl_datatype_hash(datatype),
                                   uhset_hash(CowlFacetRestrSet, restrictions));

    CowlDatatypeRestr init = {
        .super = COWL_DATA_RANGE_INIT(CDRT_DATATYPE_RESTRICTION, hash),
        .datatype = cowl_datatype_retain(datatype),
        .restrictions = restrictions
    };

    cowl_struct(CowlDatatypeRestr) *restr = malloc(sizeof(*restr));
    memcpy(restr, &init, sizeof(*restr));
    return restr;
}

static void cowl_datatype_restr_free(CowlDatatypeRestr *restr) {
    if (!restr) return;
    cowl_datatype_release(restr->datatype);
    cowl_facet_restr_set_free(restr->restrictions);
    free((void *)restr);
}

CowlDatatypeRestr* cowl_datatype_restr_get(CowlDatatype *datatype, CowlFacetRestrSet *restr) {
    return cowl_datatype_restr_alloc(datatype, restr);
}

CowlDatatypeRestr* cowl_datatype_restr_retain(CowlDatatypeRestr *restr) {
    return cowl_data_range_ref_incr(restr);
}

void cowl_datatype_restr_release(CowlDatatypeRestr *restr) {
    if (restr && !cowl_data_range_ref_decr(restr)) {
        cowl_datatype_restr_free(restr);
    }
}

CowlDatatype* cowl_datatype_restr_get_datatype(CowlDatatypeRestr *restr) {
    return restr->datatype;
}

CowlFacetRestrSet* cowl_datatype_restr_get_restrictions(CowlDatatypeRestr *restr) {
    return restr->restrictions;
}

bool cowl_datatype_restr_equals(CowlDatatypeRestr *lhs, CowlDatatypeRestr *rhs) {
    return cowl_datatype_equals(lhs->datatype, rhs->datatype) &&
           uhset_equals(CowlFacetRestrSet, lhs->restrictions, rhs->restrictions);
}

cowl_uint_t cowl_datatype_restr_hash(CowlDatatypeRestr *restr) {
    return cowl_data_range_hash_get(restr);
}

bool cowl_datatype_restr_iterate_signature(CowlDatatypeRestr *restr, void *ctx,
                                           CowlEntityIterator iter) {
    if (!cowl_datatype_iterate_signature(restr->datatype, ctx, iter)) return false;

    uhash_foreach_key(CowlFacetRestrSet, restr->restrictions, facet_restr, {
        if (!cowl_facet_restr_iterate_signature(facet_restr, ctx, iter)) return false;
    });

    return true;
}