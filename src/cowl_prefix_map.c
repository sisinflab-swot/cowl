/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_prefix_map.h"
#include "cowl_any.h"
#include "cowl_config.h"
#include "cowl_iri.h"
#include "cowl_object.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_prefix_map_private.h"
#include "cowl_ret.h"
#include "cowl_string.h"
#include "cowl_string_private.h"
#include "cowl_table.h"
#include "cowl_table_private.h"
#include "cowl_vocab.h"
#include "ulib.h"
#include <stddef.h>

static CowlString *RESERVED_PN[4][2] = { 0 };

cowl_ret cowl_prefix_map_api_init(void) {
    CowlVocab const *v = cowl_vocab();
    RESERVED_PN[0][0] = v->owl->prefix;
    RESERVED_PN[0][1] = v->owl->ns;
    RESERVED_PN[1][0] = v->rdf->prefix;
    RESERVED_PN[1][1] = v->rdf->ns;
    RESERVED_PN[2][0] = v->rdfs->prefix;
    RESERVED_PN[2][1] = v->rdfs->ns;
    RESERVED_PN[3][0] = v->xsd->prefix;
    RESERVED_PN[3][1] = v->xsd->ns;
    return COWL_OK;
}

void cowl_prefix_map_api_deinit(void) {
    // No-op.
}

static inline bool is_dirty(CowlPrefixMap *map) {
    return cowl_get_bit(map);
}

static inline void set_dirty(CowlPrefixMap *map) {
    cowl_set_bit(map);
}

static inline void set_clean(CowlPrefixMap *map) {
    cowl_unset_bit(map);
}

static cowl_ret update_reverse_map(CowlPrefixMap *map) {
    if (!is_dirty(map)) return COWL_OK;

    CowlTable *h1 = map->prefix_ns;
    CowlTable *h2 = map->ns_prefix;

    cowl_table_foreach (h1, e) {
        ulib_uint i;
        ulib_ret const ret = uhash_put(CowlObjectPtr, &h2->data, *e.val, &i);
        if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
        if (ret == ULIB_OK) {
            uhmap_set_val(CowlObjectPtr, &h2->data, i, *e.key);
            continue;
        }
        // Namespace already mapped to another prefix, keep the shortest one.
        CowlString *ex = uhmap_val(CowlObjectPtr, &h2->data, i);
        if (cowl_string_get_length(*e.key) < cowl_string_get_length(ex)) {
            uhmap_set_val(CowlObjectPtr, &h2->data, i, *e.key);
        }
    }

    set_clean(map);
    return COWL_OK;
}

static cowl_ret register_reserved(CowlPrefixMap *map) {
    for (unsigned i = 0; i < ulib_array_count(RESERVED_PN); ++i) {
        cowl_ret ret = cowl_prefix_map_add(map, RESERVED_PN[i][0], RESERVED_PN[i][1], false);
        if (cowl_is_err(ret)) return ret;
    }
    return COWL_OK;
}

CowlPrefixMap *cowl_prefix_map(void) {
    CowlPrefixMap *map = ulib_alloc(map);
    if (!map) goto err;

    *map = (CowlPrefixMap){ .super = COWL_OBJECT_INIT(COWL_OT_PREFIX_MAP) };
    if (cowl_is_err(register_reserved(map))) goto err;

    CowlPrefixMap *d_map = cowl_get_prefix_map();
    if (d_map && cowl_is_err(cowl_prefix_map_merge(map, d_map, false))) goto err;
    return map;

err:
    if (map) cowl_prefix_map_free(map);
    return NULL;
}

void cowl_prefix_map_free(CowlPrefixMap *map) {
    cowl_table_release_ex(map->prefix_ns, true);
    cowl_table_release_ex(map->ns_prefix, false);
    ulib_free(map);
}

CowlTable *cowl_prefix_map_get_table(CowlPrefixMap *map, bool reverse) {
    CowlTable **table = reverse ? &map->ns_prefix : &map->prefix_ns;

    if (!*table) {
        UHash(CowlObjectPtr) temp = cowl_string_map();
        if (!(*table = cowl_table(&temp))) return NULL;
    }

    if (reverse && update_reverse_map(map)) return NULL;

    return *table;
}

CowlString *cowl_prefix_map_get_ns(CowlPrefixMap *map, CowlString *prefix) {
    return cowl_table_get_value(cowl_prefix_map_get_table(map, false), prefix);
}

CowlString *cowl_prefix_map_get_prefix(CowlPrefixMap *map, CowlString *ns) {
    return cowl_table_get_value(cowl_prefix_map_get_table(map, true), ns);
}

static CowlString *intern_ns(CowlString *prefix, CowlString *ns) {
    for (unsigned i = 0; i < ulib_array_count(RESERVED_PN); ++i) {
        if (cowl_string_equals(prefix, RESERVED_PN[i][0])) return RESERVED_PN[i][1];
    }
    return cowl_string_intern(ns);
}

cowl_ret
cowl_prefix_map_add(CowlPrefixMap *map, CowlString *prefix, CowlString *ns, bool overwrite) {
    CowlTable *table = cowl_prefix_map_get_table(map, false);
    if (!(table && (ns = intern_ns(prefix, ns)))) return COWL_ERR_MEM;

    ulib_uint i;
    ulib_ret ret = uhash_put(CowlObjectPtr, &table->data, prefix, &i);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);

    if (ret == ULIB_NO) {
        if (!overwrite) return COWL_NO;
        cowl_release(uhmap_val(CowlObjectPtr, &table->data, i));
        uhmap_set_val(CowlObjectPtr, &table->data, i, cowl_retain(ns));
        set_dirty(map);
        return COWL_OK;
    }

    uhash_set_key(CowlObjectPtr, &table->data, i, cowl_retain(prefix));
    uhmap_set_val(CowlObjectPtr, &table->data, i, cowl_retain(ns));
    set_dirty(map);
    return COWL_OK;
}

cowl_ret cowl_prefix_map_add_raw(CowlPrefixMap *map, UString prefix, UString ns, bool overwrite) {
    cowl_ret ret = COWL_ERR_MEM;
    CowlString *prefix_str = NULL;
    CowlString *ns_str = NULL;
    if (!(prefix_str = cowl_string_opt(prefix, COWL_SO_COPY))) goto end;
    if (!(ns_str = cowl_string_opt(ns, COWL_SO_COPY | COWL_SO_INTERN))) goto end;
    ret = cowl_prefix_map_add(map, prefix_str, ns_str, overwrite);
end:
    cowl_release(prefix_str);
    cowl_release(ns_str);
    return ret;
}

cowl_ret cowl_prefix_map_remove_prefix_raw(CowlPrefixMap *map, UString prefix) {
    CowlString prefix_local = cowl_string_init(prefix);
    return cowl_prefix_map_remove_prefix(map, &prefix_local);
}

cowl_ret cowl_prefix_map_remove_prefix(CowlPrefixMap *map, CowlString *prefix) {
    CowlTable *table = cowl_prefix_map_get_table(map, false);
    if (!table) return COWL_ERR_MEM;

    cowl_ret ret = COWL_NO;
    CowlAny *ex_key;
    CowlAny *ex_value;

    if (uhmap_pop(CowlObjectPtr, &table->data, prefix, &ex_key, &ex_value)) {
        if (!(table = cowl_prefix_map_get_table(map, true))) return COWL_ERR_MEM;
        ulib_uint i = uhash_get(CowlObjectPtr, &table->data, ex_value);
        if (i != UHASH_INDEX_MISSING && ex_key == uhmap_val(CowlObjectPtr, &table->data, i)) {
            uhash_delete(CowlObjectPtr, &table->data, i);
            // We need to set the map as dirty because we don't know if there are other prefixes
            // associated with the same namespace, so the reverse map may be inconsistent.
            set_dirty(map);
        }
        cowl_release(ex_key);
        cowl_release(ex_value);
        ret = COWL_OK;
    }

    return ret;
}

cowl_ret cowl_prefix_map_remove_ns_raw(CowlPrefixMap *map, UString ns) {
    CowlString ns_local = cowl_string_init(ns);
    return cowl_prefix_map_remove_ns(map, &ns_local);
}

cowl_ret cowl_prefix_map_remove_ns(CowlPrefixMap *map, CowlString *ns) {
    CowlTable *table = cowl_prefix_map_get_table(map, false);
    if (!table) return COWL_ERR_MEM;

    cowl_ret ret = COWL_NO;
    uhash_foreach (CowlObjectPtr, &table->data, it) {
        if (!cowl_string_equals(*it.val, ns)) continue;
        cowl_release(*it.key);
        cowl_release(*it.val);
        uhash_delete(CowlObjectPtr, &table->data, it.i);
        ret = COWL_OK;
    }

    if (!(table = cowl_prefix_map_get_table(map, true))) return COWL_ERR_MEM;
    uhmap_remove(CowlObjectPtr, &table->data, ns);

    // No need to mark the map as dirty: we deleted all the prefixes associated with the namespace
    // and we updated the reverse map, so if the two maps were consistent they still are.

    return ret;
}

cowl_ret cowl_prefix_map_merge(CowlPrefixMap *dst, CowlPrefixMap *src, bool overwrite) {
    CowlTable *table = cowl_prefix_map_get_table(src, false);
    if (!table) return COWL_ERR_MEM;
    cowl_ret ret = COWL_NO;
    cowl_table_foreach (table, e) {
        cowl_ret lret = cowl_prefix_map_add(dst, *e.key, *e.val, overwrite);
        if (cowl_is_err(lret)) return lret;
        if (lret == COWL_OK) ret = COWL_OK;
    }
    return ret;
}

CowlIRI *cowl_prefix_map_get_iri(CowlPrefixMap *map, UString prefix, UString rem) {
    CowlString prefix_local = cowl_string_init(prefix);
    CowlString *prefix_str = cowl_prefix_map_get_ns(map, &prefix_local);
    if (!prefix_str) return NULL;

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string_opt(rem, COWL_SO_COPY) : cowl_string_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri(prefix_str, rem_str);
    cowl_release(rem_str);
    return iri;
}

CowlIRI *cowl_prefix_map_parse_short_iri(CowlPrefixMap *map, UString short_iri) {
    char const *str = ustring_data(short_iri);
    ulib_uint const str_length = ustring_length(short_iri);
    ulib_uint const ns_length = ustring_index_of(short_iri, ':');

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length + 1, str_length - (ns_length + 1));
    return cowl_prefix_map_get_iri(map, ns, rem);
}

CowlIRI *cowl_prefix_map_parse_iri(CowlPrefixMap *map, UString str) {
    CowlIRI *iri = cowl_prefix_map_parse_short_iri(map, str);
    return iri ? iri : cowl_iri_from_string(str);
}
