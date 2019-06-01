/// @author Ivano Bilenchi

#include "cowl_data_range_private.h"
#include "cowl_datatype.h"
#include "cowl_data_compl.h"
#include "cowl_data_one_of.h"
#include "cowl_nary_data.h"

CowlDataRange* cowl_data_range_retain(CowlDataRange *range) {
    return cowl_data_range_ref_incr(range);
}

void cowl_data_range_release(CowlDataRange *range) {
    if (!range) return;

#define GEN_CASE_RELEASE(CDRT, TYPE, PREFIX) \
    case CDRT: PREFIX##_release((TYPE *)range); break

    switch (range->type) {

        GEN_CASE_RELEASE(CDRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_RELEASE(CDRT_DATA_INTERSECTION, CowlNAryData, cowl_nary_data);
        GEN_CASE_RELEASE(CDRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_RELEASE(CDRT_DATA_COMPLEMENT, CowlDataCompl, cowl_data_compl);
        GEN_CASE_RELEASE(CDRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            break;
    }
}

CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range) {
    return range->type;
}

bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs) {
    if (lhs == rhs) return true;
    if (lhs->type != rhs->type || lhs->super.hash != rhs->super.hash) return false;

#define GEN_CASE_EQUAL(CDRT, TYPE, PREFIX) \
    case CDRT: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(CDRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_EQUAL(CDRT_DATA_INTERSECTION, CowlNAryData, cowl_nary_data);
        GEN_CASE_EQUAL(CDRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_EQUAL(CDRT_DATA_COMPLEMENT, CowlDataCompl, cowl_data_compl);
        GEN_CASE_EQUAL(CDRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            return false;
    }
}

cowl_uint_t cowl_data_range_hash(CowlDataRange *range) {
    return cowl_data_range_hash_get(range);
}

bool cowl_data_range_iterate_signature(CowlDataRange *range, void *ctx, CowlEntityIterator iter) {

#define GEN_CASE_SIG(CDRT, TYPE, PREFIX) \
    case CDRT: return PREFIX##_iterate_signature((TYPE *)range, ctx, iter)

    switch (range->type) {

        GEN_CASE_SIG(CDRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_SIG(CDRT_DATA_INTERSECTION, CowlNAryData, cowl_nary_data);
        GEN_CASE_SIG(CDRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_SIG(CDRT_DATA_COMPLEMENT, CowlDataCompl, cowl_data_compl);
        GEN_CASE_SIG(CDRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            return true;
    }
}
