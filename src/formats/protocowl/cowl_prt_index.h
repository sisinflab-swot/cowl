/**
 * @author Valerio Di Ceglie
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRT_INDEX_H
#define COWL_PRT_INDEX_H

#include "cowl.h"
#include "ulib.h"

typedef struct CowlPRTPrefixMap {
    UVec(CowlObjectPtr) _idx_to_ns;
    UHash(CowlObjectTable) _ns_to_idx;
    UHash(CowlObjectTable) _ns_to_prefix;
    ulib_uint _encode_idx;
    ulib_uint _sep;
} CowlPRTPrefixMap;

typedef struct CowlPRTIdMap {
    UVec(CowlObjectPtr) _idx_to_id;
    UHash(CowlObjectTable) _id_to_idx;
    ulib_uint _encode_idx;
    ulib_uint _sep;
} CowlPRTIdMap;

typedef struct CowlPRTIndex {
    CowlPRTPrefixMap _pmap;
    CowlPRTIdMap _imap;
} CowlPRTIndex;

typedef void CowlIRIOrAnonInd;

#define COWL_PRT_NOT_FOUND ((ulib_uint)(-1))
#define COWL_PRT_STANDARD_PREFIX_COUNT 5

cowl_ret cowl_prt_index_init(CowlPRTIndex *index, bool encode);
void cowl_prt_index_deinit(CowlPRTIndex *index);
cowl_ret cowl_prt_index_reserve_ids(CowlPRTIndex *index, ulib_uint count);

ulib_uint cowl_prt_index_prefix_count(CowlPRTIndex const *index);
ulib_uint cowl_prt_index_id_count(CowlPRTIndex const *index);

CowlString *cowl_prt_index_get_ns(CowlPRTIndex const *index, ulib_uint idx);
CowlString *cowl_prt_index_get_prefix(CowlPRTIndex const *index, CowlString *ns);
ulib_uint cowl_prt_index_get_ns_idx(CowlPRTIndex const *index, CowlString *ns);

CowlIRIOrAnonInd *cowl_prt_index_get_id(CowlPRTIndex *index, ulib_uint idx);
ulib_uint cowl_prt_index_get_id_idx(CowlPRTIndex const *index, CowlIRIOrAnonInd *id);

cowl_ret cowl_prt_index_add_prefix(CowlPRTIndex *index, CowlString *ns, CowlString *prefix);
cowl_ret cowl_prt_index_add_primitive(CowlPRTIndex *index, CowlAnyPrimitive *primitive);

cowl_ret cowl_prt_index_reset_prefixes(CowlPRTIndex *index);
cowl_ret cowl_prt_index_reset_ids(CowlPRTIndex *index);

void cowl_prt_index_unencoded_prefixes(CowlPRTIndex *index, UVec(CowlObjectPtr) *prefix_view,
                                       UVec(CowlObjectPtr) *ns_view);
void cowl_prt_index_unencoded_ids(CowlPRTIndex *index, UVec(CowlObjectPtr) *iri_view,
                                  UVec(CowlObjectPtr) *anon_view);

#endif // COWL_PRT_INDEX_H
