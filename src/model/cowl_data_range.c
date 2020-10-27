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
#include "cowl_template.h"

CowlDataRange* cowl_data_range_retain(CowlDataRange *range) {
    return cowl_object_retain(range);
}

void cowl_data_range_release(CowlDataRange *range) {
    if (!range) return;

#define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)range); break

    switch (cowl_data_range_get_type(range)) {
        case COWL_DRT_DATATYPE: GEN_RELEASE(Datatype, datatype);
        case COWL_DRT_DATATYPE_RESTR: GEN_RELEASE(DatatypeRestr, datatype_restr);
        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION: GEN_RELEASE(NAryData, nary_data);
        case COWL_DRT_DATA_COMPL: GEN_RELEASE(DataCompl, data_compl);
        case COWL_DRT_DATA_ONE_OF: GEN_RELEASE(DataOneOf, data_one_of);
        default: break;
    }
}

CowlDataRangeType cowl_data_range_get_type(CowlDataRange *range) {
    return (CowlDataRangeType)(cowl_get_type(range) - COWL_OT_DR_DATATYPE);
}

CowlString* cowl_data_range_to_string(CowlDataRange *range)
    COWL_TO_STRING_IMPL(data_range, range)

bool cowl_data_range_equals(CowlDataRange *lhs, CowlDataRange *rhs) {
    if (lhs == rhs) return true;
    if (!cowl_hash_object_equals_impl(lhs, rhs)) return false;

#define GEN_EQUAL(UC, LC) return cowl_##LC##_equals((Cowl##UC *)lhs, (Cowl##UC *)rhs)

    switch (cowl_data_range_get_type(lhs)) {
        case COWL_DRT_DATATYPE: GEN_EQUAL(Datatype, datatype);
        case COWL_DRT_DATATYPE_RESTR: GEN_EQUAL(DatatypeRestr, datatype_restr);
        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION: GEN_EQUAL(NAryData, nary_data);
        case COWL_DRT_DATA_COMPL: GEN_EQUAL(DataCompl, data_compl);
        case COWL_DRT_DATA_ONE_OF: GEN_EQUAL(DataOneOf, data_one_of);
        default: return false;
    }
}

cowl_uint_t cowl_data_range_hash(CowlDataRange *range) {
    return cowl_object_hash_get(range);
}

bool cowl_data_range_iterate_signature(CowlDataRange *range, CowlEntityIterator *iter) {

#define GEN_SIG(UC, LC) return cowl_##LC##_iterate_signature((Cowl##UC *)range, iter)

    switch (cowl_data_range_get_type(range)) {
        case COWL_DRT_DATATYPE: GEN_SIG(Datatype, datatype);
        case COWL_DRT_DATATYPE_RESTR: GEN_SIG(DatatypeRestr, datatype_restr);
        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION: GEN_SIG(NAryData, nary_data);
        case COWL_DRT_DATA_COMPL: GEN_SIG(DataCompl, data_compl);
        case COWL_DRT_DATA_ONE_OF: GEN_SIG(DataOneOf, data_one_of);
        default: return true;
    }
}

bool cowl_data_range_iterate_primitives(CowlDataRange *range, CowlPrimitiveIterator *iter) {

#define GEN_PRIM(UC, LC) return cowl_##LC##_iterate_primitives((Cowl##UC *)range, iter)

    switch (cowl_data_range_get_type(range)) {
        case COWL_DRT_DATATYPE: GEN_PRIM(Datatype, datatype);
        case COWL_DRT_DATATYPE_RESTR: GEN_PRIM(DatatypeRestr, datatype_restr);
        case COWL_DRT_DATA_INTERSECT:
        case COWL_DRT_DATA_UNION: GEN_PRIM(NAryData, nary_data);
        case COWL_DRT_DATA_COMPL: GEN_PRIM(DataCompl, data_compl);
        case COWL_DRT_DATA_ONE_OF: GEN_PRIM(DataOneOf, data_one_of);
        default: return true;
    }
}
