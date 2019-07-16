/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_range_private.h"
#include "cowl_datatype.h"
#include "cowl_datatype_restr.h"
#include "cowl_data_compl.h"
#include "cowl_data_one_of.h"
#include "cowl_nary_data.h"
#include "cowl_str_buf.h"

CowlDataRange* cowl_data_range_retain(CowlDataRange *range) {
    return cowl_object_retain(range);
}

void cowl_data_range_release(CowlDataRange *range) {
    if (!range) return;

#define GEN_CASE_RELEASE(CDRT, TYPE, PREFIX) \
    case CDRT: PREFIX##_release((TYPE *)range); break

    switch (range->type) {

        GEN_CASE_RELEASE(COWL_DRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_RELEASE(COWL_DRT_DATATYPE_RESTR, CowlDatatypeRestr, cowl_datatype_restr);
        GEN_CASE_RELEASE(COWL_DRT_DATA_INTERSECT, CowlNAryData, cowl_nary_data);
        GEN_CASE_RELEASE(COWL_DRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_RELEASE(COWL_DRT_DATA_COMPL, CowlDataCompl, cowl_data_compl);
        GEN_CASE_RELEASE(COWL_DRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            break;
    }
}

CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range) {
    return range->type;
}

CowlString* cowl_data_range_to_string(CowlDataRange *range) {
    CowlStrBuf *buf = cowl_str_buf_alloc();
    cowl_str_buf_append_data_range(buf, range);
    return cowl_str_buf_to_string(buf);
}

bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs) {
    if (lhs == rhs) return true;
    if (lhs->type != rhs->type || lhs->super.hash != rhs->super.hash) return false;

#define GEN_CASE_EQUAL(CDRT, TYPE, PREFIX) \
    case CDRT: return PREFIX##_equals((TYPE *)lhs, (TYPE *)rhs)

    switch (lhs->type) {

        GEN_CASE_EQUAL(COWL_DRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_EQUAL(COWL_DRT_DATATYPE_RESTR, CowlDatatypeRestr, cowl_datatype_restr);
        GEN_CASE_EQUAL(COWL_DRT_DATA_INTERSECT, CowlNAryData, cowl_nary_data);
        GEN_CASE_EQUAL(COWL_DRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_EQUAL(COWL_DRT_DATA_COMPL, CowlDataCompl, cowl_data_compl);
        GEN_CASE_EQUAL(COWL_DRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            return false;
    }
}

cowl_uint_t cowl_data_range_hash(CowlDataRange *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_range_iterate_signature(CowlDataRange *range, CowlEntityIterator *iter) {

#define GEN_CASE_SIG(CDRT, TYPE, PREFIX) \
    case CDRT: return PREFIX##_iterate_signature((TYPE *)range, iter)

    switch (range->type) {

        GEN_CASE_SIG(COWL_DRT_DATATYPE, CowlDatatype, cowl_datatype);
        GEN_CASE_SIG(COWL_DRT_DATATYPE_RESTR, CowlDatatypeRestr, cowl_datatype_restr);
        GEN_CASE_SIG(COWL_DRT_DATA_INTERSECT, CowlNAryData, cowl_nary_data);
        GEN_CASE_SIG(COWL_DRT_DATA_UNION, CowlNAryData, cowl_nary_data);
        GEN_CASE_SIG(COWL_DRT_DATA_COMPL, CowlDataCompl, cowl_data_compl);
        GEN_CASE_SIG(COWL_DRT_DATA_ONE_OF, CowlDataOneOf, cowl_data_one_of);

        default:
            return true;
    }
}
