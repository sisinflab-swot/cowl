/**
 * @author Valerio Di Ceglie
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_prt_index.h"
#include "cowl.h"
#include "ulib.h"
#include <stddef.h>
#include <stdint.h>

static inline void *uintptr_to_void(uintptr_t ptr) {
    // NOLINTBEGIN(performance-no-int-to-ptr)
    return (void *)ptr;
    // NOLINTEND(performance-no-int-to-ptr)
}

// Prefix map

static inline bool prefix_map_is_encoding(CowlPRTPrefixMap const *map) {
    return map->_encode_idx < ULIB_UINT_MAX;
}

static void prefix_map_deinit(CowlPRTPrefixMap *map) {
    uhash_foreach (CowlObjectTable, &map->_ns_to_prefix, e) {
        cowl_release(*e.val);
    }
    uvec_foreach (CowlObjectPtr, &map->_idx_to_ns, e) {
        cowl_release(*e.item);
    }
    uvec_deinit(CowlObjectPtr, &map->_idx_to_ns);
    uhash_deinit(CowlObjectTable, &map->_ns_to_idx);
    uhash_deinit(CowlObjectTable, &map->_ns_to_prefix);
}

static inline void prefix_map_sync_unencoded(CowlPRTPrefixMap *map) {
    UVec(CowlObjectPtr) unencoded = uvec_view_from(CowlObjectPtr, &map->_idx_to_ns,
                                                   map->_encode_idx);
    uvec_foreach (CowlObjectPtr, &unencoded, e) {
        // key can never be UHASH_NOT_FOUND if the map is correctly populated.
        ulib_uint const key = uhash_get(CowlObjectTable, &map->_ns_to_idx, *e.item);
        ulib_uint const idx = map->_encode_idx + e.i;
        uhash_value(CowlObjectTable, &map->_ns_to_idx, key) = uintptr_to_void(idx);
    }
    map->_encode_idx = uvec_count(CowlObjectPtr, &map->_idx_to_ns);
    map->_sep = map->_encode_idx;
}

static inline cowl_ret
prefix_map_add_encoding(CowlPRTPrefixMap *map, CowlString *ns, CowlString *prefix) {
    ulib_uint ns_idx;

    ulib_ret ret = uhash_put(CowlObjectTable, &map->_ns_to_idx, ns, &ns_idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    if (ret == ULIB_NO) return COWL_OK;

    ulib_uint const count = uvec_count(CowlObjectPtr, &map->_idx_to_ns);

    if (prefix) {
        if (count > map->_sep) {
            // Move the first unencoded namespace to the end of the vector.
            CowlString *first = uvec_get(CowlObjectPtr, &map->_idx_to_ns, map->_sep);
            if (uvec_push(CowlObjectPtr, &map->_idx_to_ns, first)) return COWL_ERR_MEM;
            uvec_set(CowlObjectPtr, &map->_idx_to_ns, map->_sep, ns);
        } else if (uvec_push(CowlObjectPtr, &map->_idx_to_ns, ns)) {
            return COWL_ERR_MEM;
        }
        map->_sep++;
    } else if (uvec_push(CowlObjectPtr, &map->_idx_to_ns, ns)) {
        return COWL_ERR_MEM;
    }

    if (prefix) {
        ulib_uint prefix_idx;
        ret = uhash_put(CowlObjectTable, &map->_ns_to_prefix, ns, &prefix_idx);
        if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
        uhash_value(CowlObjectTable, &map->_ns_to_prefix, prefix_idx) = cowl_retain(prefix);
    }

    cowl_retain(ns);
    return COWL_OK;
}

static inline cowl_ret prefix_map_add_decoding(CowlPRTPrefixMap *map, CowlString *ns) {
    if (uvec_push(CowlObjectPtr, &map->_idx_to_ns, ns)) return COWL_ERR_MEM;
    cowl_retain(ns);
    return COWL_OK;
}

static cowl_ret prefix_map_add(CowlPRTPrefixMap *map, CowlString *ns, CowlString *prefix) {
    return prefix_map_is_encoding(map) ? prefix_map_add_encoding(map, ns, prefix)
                                       : prefix_map_add_decoding(map, ns);
}

static cowl_ret prefix_map_add_standard_prefixes(CowlPRTPrefixMap *map) {
    const CowlVocab *vocab = cowl_vocab();
    // Update COWL_PRT_STANDARD_PREFIX_COUNT if you change the number of standard prefixes.
    CowlString *ns[] = {
        vocab->rdf->ns, vocab->rdfs->ns, vocab->xsd->ns, vocab->owl->ns, vocab->xml->ns,
    };
    CowlString *prefix[] = {
        vocab->rdf->prefix, vocab->rdfs->prefix, vocab->xsd->prefix,
        vocab->owl->prefix, vocab->xml->prefix,
    };
    cowl_ret ret = COWL_OK;
    for (ulib_uint i = 0; i < COWL_PRT_STANDARD_PREFIX_COUNT; ++i) {
        if ((ret = prefix_map_add(map, ns[i], prefix[i]))) break;
    }
    return ret;
}

static cowl_ret prefix_map_init(CowlPRTPrefixMap *map, bool encode) {
    map->_idx_to_ns = uvec(CowlObjectPtr);
    map->_ns_to_idx = uhmap(CowlObjectTable);
    map->_ns_to_prefix = uhmap(CowlObjectTable);

    if (prefix_map_add_standard_prefixes(map)) {
        prefix_map_deinit(map);
        return COWL_ERR_MEM;
    }

    if (encode) {
        prefix_map_sync_unencoded(map);
    } else {
        map->_encode_idx = ULIB_UINT_MAX;
    }

    return COWL_OK;
}

static cowl_ret prefix_map_reset(CowlPRTPrefixMap *map) {
    bool const encode = prefix_map_is_encoding(map);
    prefix_map_deinit(map);
    return prefix_map_init(map, encode);
}

static ulib_uint prefix_map_count(CowlPRTPrefixMap const *map) {
    return uvec_count(CowlObjectPtr, &map->_idx_to_ns);
}

static void prefix_map_unencoded(CowlPRTPrefixMap *map, UVec(CowlObjectPtr) *prefixes,
                                 UVec(CowlObjectPtr) *ns) {
    *prefixes = uvec_view(CowlObjectPtr, &map->_idx_to_ns, map->_encode_idx,
                          map->_sep - map->_encode_idx);
    *ns = uvec_view_from(CowlObjectPtr, &map->_idx_to_ns, map->_sep);
    prefix_map_sync_unencoded(map);
}

static CowlString *prefix_map_get(CowlPRTPrefixMap const *map, ulib_uint idx) {
    return uvec_get(CowlObjectPtr, &map->_idx_to_ns, idx);
}

static CowlString *prefix_map_get_prefix(CowlPRTPrefixMap const *map, CowlString *ns) {
    return uhmap_get(CowlObjectTable, &map->_ns_to_prefix, ns, NULL);
}

static ulib_uint prefix_map_get_idx(CowlPRTPrefixMap const *map, CowlString *ns) {
    uintptr_t idx = (uintptr_t)uhmap_get(CowlObjectTable, &map->_ns_to_idx, ns,
                                         uintptr_to_void(COWL_PRT_NOT_FOUND));
    return (ulib_uint)idx;
}

// ID map

static inline bool id_map_is_encoding(CowlPRTIdMap const *map) {
    return map->_encode_idx < ULIB_UINT_MAX;
}

static void id_map_init(CowlPRTIdMap *map, bool encode) {
    map->_idx_to_id = uvec(CowlObjectPtr);
    map->_id_to_idx = uhmap(CowlObjectTable);
    map->_encode_idx = encode ? 0 : ULIB_UINT_MAX;
    map->_sep = 0;
}

static void id_map_deinit(CowlPRTIdMap *map) {
    uvec_foreach (CowlObjectPtr, &map->_idx_to_id, e) {
        cowl_release(*e.item);
    }
    uvec_deinit(CowlObjectPtr, &map->_idx_to_id);
    uhash_deinit(CowlObjectTable, &map->_id_to_idx);
}

static void id_map_reset(CowlPRTIdMap *map) {
    bool const encode = id_map_is_encoding(map);
    id_map_deinit(map);
    id_map_init(map, encode);
}

static cowl_ret id_map_reserve(CowlPRTIdMap *map, ulib_uint count) {
    if (uvec_reserve(CowlObjectPtr, &map->_idx_to_id, count)) return COWL_ERR_MEM;
    if (uhash_resize(CowlObjectTable, &map->_id_to_idx, count)) return COWL_ERR_MEM;
    return COWL_OK;
}

static ulib_uint id_map_count(CowlPRTIdMap const *map) {
    return uvec_count(CowlObjectPtr, &map->_idx_to_id);
}

static void id_map_sync_unencoded(CowlPRTIdMap *map) {
    UVec(CowlObjectPtr) unencoded = uvec_view_from(CowlObjectPtr, &map->_idx_to_id,
                                                   map->_encode_idx);
    uvec_foreach (CowlObjectPtr, &unencoded, e) {
        // key can never be UHASH_NOT_FOUND if the map is correctly populated.
        ulib_uint const key = uhash_get(CowlObjectTable, &map->_id_to_idx, *e.item);
        ulib_uint const idx = map->_encode_idx + e.i;
        uhash_value(CowlObjectTable, &map->_id_to_idx, key) = uintptr_to_void(idx);
    }
    map->_encode_idx = uvec_count(CowlObjectPtr, &map->_idx_to_id);
    map->_sep = map->_encode_idx;
}

static void
id_map_unencoded(CowlPRTIdMap *map, UVec(CowlObjectPtr) *iris, UVec(CowlObjectPtr) *anons) {
    *iris = uvec_view(CowlObjectPtr, &map->_idx_to_id, map->_encode_idx,
                      map->_sep - map->_encode_idx);
    *anons = uvec_view_from(CowlObjectPtr, &map->_idx_to_id, map->_sep);
    id_map_sync_unencoded(map);
}

static ulib_uint id_map_get_idx(CowlPRTIdMap const *map, CowlIRIOrAnonInd *id) {
    uintptr_t idx = (uintptr_t)uhmap_get(CowlObjectTable, &map->_id_to_idx, id,
                                         uintptr_to_void(COWL_PRT_NOT_FOUND));
    return (ulib_uint)idx;
}

static inline cowl_ret id_map_add_encoding(CowlPRTIdMap *map, CowlIRIOrAnonInd *id, bool is_iri) {
    ulib_uint tbl_idx;

    ulib_ret ret = uhash_put(CowlObjectTable, &map->_id_to_idx, id, &tbl_idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    if (ret == ULIB_NO) return COWL_OK;

    ulib_uint const count = uvec_count(CowlObjectPtr, &map->_idx_to_id);

    if (is_iri) {
        if (count > map->_sep) {
            CowlAnonInd *first = uvec_get(CowlObjectPtr, &map->_idx_to_id, map->_sep);
            if (uvec_push(CowlObjectPtr, &map->_idx_to_id, first)) return COWL_ERR_MEM;
            uvec_set(CowlObjectPtr, &map->_idx_to_id, map->_sep, id);
        } else if (uvec_push(CowlObjectPtr, &map->_idx_to_id, id)) {
            return COWL_ERR_MEM;
        }
        map->_sep++;
    } else if (uvec_push(CowlObjectPtr, &map->_idx_to_id, id)) {
        return COWL_ERR_MEM;
    }

    cowl_retain(id);
    return COWL_OK;
}

static inline cowl_ret id_map_add_decoding(CowlPRTIdMap *map, CowlIRIOrAnonInd *id) {
    if (uvec_push(CowlObjectPtr, &map->_idx_to_id, id)) return COWL_ERR_MEM;
    cowl_retain(id);
    return COWL_OK;
}

static cowl_ret id_map_add(CowlPRTIdMap *map, CowlIRIOrAnonInd *id, bool is_iri) {
    return id_map_is_encoding(map) ? id_map_add_encoding(map, id, is_iri)
                                   : id_map_add_decoding(map, id);
}

static CowlIRIOrAnonInd *id_map_get(CowlPRTIdMap *map, ulib_uint idx) {
    if (idx < uvec_count(CowlObjectPtr, &map->_idx_to_id)) {
        return uvec_get(CowlObjectPtr, &map->_idx_to_id, idx);
    }
    // Index out of bounds, generate a fresh anonymous individual.
    CowlAnonInd *ind = cowl_anon_ind(NULL);
    CowlIRIOrAnonInd *ret = NULL;
    ret = (ind && id_map_add(map, ind, false) == COWL_OK) ? ind : NULL;
    cowl_release(ind);
    return ret;
}

// Public API

cowl_ret cowl_prt_index_init(CowlPRTIndex *index, bool encode) {
    id_map_init(&index->_imap, encode);
    return prefix_map_init(&index->_pmap, encode);
}

void cowl_prt_index_deinit(CowlPRTIndex *index) {
    prefix_map_deinit(&index->_pmap);
    id_map_deinit(&index->_imap);
}

cowl_ret cowl_prt_index_reserve_ids(CowlPRTIndex *index, ulib_uint count) {
    return id_map_reserve(&index->_imap, count);
}

ulib_uint cowl_prt_index_prefix_count(CowlPRTIndex const *index) {
    return prefix_map_count(&index->_pmap);
}

ulib_uint cowl_prt_index_id_count(CowlPRTIndex const *index) {
    return id_map_count(&index->_imap);
}

CowlString *cowl_prt_index_get_ns(CowlPRTIndex const *index, ulib_uint idx) {
    return prefix_map_get(&index->_pmap, idx);
}

CowlString *cowl_prt_index_get_prefix(CowlPRTIndex const *index, CowlString *ns) {
    return prefix_map_get_prefix(&index->_pmap, ns);
}

ulib_uint cowl_prt_index_get_ns_idx(CowlPRTIndex const *index, CowlString *ns) {
    return prefix_map_get_idx(&index->_pmap, ns);
}

CowlIRIOrAnonInd *cowl_prt_index_get_id(CowlPRTIndex *index, ulib_uint idx) {
    return id_map_get(&index->_imap, idx);
}

ulib_uint cowl_prt_index_get_id_idx(CowlPRTIndex const *index, CowlIRIOrAnonInd *id) {
    return id_map_get_idx(&index->_imap, id);
}

cowl_ret cowl_prt_index_add_prefix(CowlPRTIndex *index, CowlString *ns, CowlString *prefix) {
    return prefix_map_add(&index->_pmap, ns, prefix);
}

static inline cowl_ret add_iri_ns(CowlPRTIndex *index, CowlIRI *iri) {
    return prefix_map_add(&index->_pmap, cowl_iri_get_ns(iri), NULL);
}

static inline bool is_encoding(CowlPRTIndex const *index) {
    return id_map_is_encoding(&index->_imap);
}

cowl_ret cowl_prt_index_add_primitive(CowlPRTIndex *index, CowlAnyPrimitive *primitive) {
    CowlIRIOrAnonInd *id = cowl_get_iri(primitive);
    bool const is_iri = !!id;

    if (is_iri) {
        if (is_encoding(index) && add_iri_ns(index, id)) return COWL_ERR_MEM;
    } else {
        id = primitive;
    }

    return id_map_add(&index->_imap, id, is_iri);
}

cowl_ret cowl_prt_index_reset_prefixes(CowlPRTIndex *index) {
    return prefix_map_reset(&index->_pmap);
}

cowl_ret cowl_prt_index_reset_ids(CowlPRTIndex *index) {
    id_map_reset(&index->_imap);
    return COWL_OK;
}

void cowl_prt_index_unencoded_prefixes(CowlPRTIndex *index, UVec(CowlObjectPtr) *prefix_view,
                                       UVec(CowlObjectPtr) *ns_view) {
    prefix_map_unencoded(&index->_pmap, prefix_view, ns_view);
}

void cowl_prt_index_unencoded_ids(CowlPRTIndex *index, UVec(CowlObjectPtr) *iri_view,
                                  UVec(CowlObjectPtr) *anon_view) {
    id_map_unencoded(&index->_imap, iri_view, anon_view);
}
