/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_prefix_map.h"
#include "cowl_any.h"
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

static inline bool is_dirty(CowlPrefixMap *map) {
    return cowl_object_bit_get(map);
}

static inline void set_dirty(CowlPrefixMap *map) {
    cowl_object_bit_set(map);
}

static inline void set_clean(CowlPrefixMap *map) {
    cowl_object_bit_unset(map);
}

static cowl_ret update_reverse_map(CowlPrefixMap *map) {
    if (!is_dirty(map)) return COWL_OK;

    CowlTable *h1 = map->prefix_ns;
    CowlTable *h2 = map->ns_prefix;

    cowl_table_foreach (h1, e) {
        ulib_ret const ret = uhmap_set(CowlObjectTable, &h2->data, *e.val, *e.key, NULL);
        if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    }

    set_clean(map);
    return COWL_OK;
}

static cowl_ret register_reserved(CowlPrefixMap *map) {
    CowlVocab const *v = cowl_vocab();
    cowl_ret r;
    if ((r = cowl_prefix_map_add(map, v->owl->prefix, v->owl->ns, false))) return r;
    if ((r = cowl_prefix_map_add(map, v->rdf->prefix, v->rdf->ns, false))) return r;
    if ((r = cowl_prefix_map_add(map, v->rdfs->prefix, v->rdfs->ns, false))) return r;
    if ((r = cowl_prefix_map_add(map, v->xsd->prefix, v->xsd->ns, false))) return r;
    return COWL_OK;
}

CowlPrefixMap *cowl_prefix_map(void) {
    CowlPrefixMap *map = ulib_alloc(map);
    if (!map) return NULL;
    *map = (CowlPrefixMap){ .super = COWL_OBJECT_INIT(COWL_OT_PREFIX_MAP) };
    if (register_reserved(map)) {
        cowl_prefix_map_free(map);
        map = NULL;
    }
    return map;
}

void cowl_prefix_map_free(CowlPrefixMap *map) {
    cowl_table_release_ex(map->prefix_ns, true);
    cowl_table_release_ex(map->ns_prefix, false);
    ulib_free(map);
}

CowlPrefixMap *cowl_prefix_map_copy(CowlPrefixMap *map) {
    CowlPrefixMap *copy = cowl_prefix_map();
    if (copy && cowl_prefix_map_merge(copy, map, false)) {
        cowl_prefix_map_free(copy);
        copy = NULL;
    }
    return copy;
}

CowlTable *cowl_prefix_map_get_table(CowlPrefixMap *map, bool reverse) {
    CowlTable **table = reverse ? &map->ns_prefix : &map->prefix_ns;

    if (!*table) {
        UHash(CowlObjectTable) temp = cowl_string_map();
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

cowl_ret
cowl_prefix_map_add(CowlPrefixMap *map, CowlString *prefix, CowlString *ns, bool overwrite) {
    CowlTable *table = cowl_prefix_map_get_table(map, false);
    if (!(table && (ns = cowl_string_intern(ns)))) return COWL_ERR_MEM;

    ulib_uint i;
    ulib_ret const ret = uhash_put(CowlObjectTable, &table->data, prefix, &i);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);

    if (ret == ULIB_NO) {
        if (!overwrite) return COWL_OK;
        // Mapping present, overwrite mapped namespace unless the prefix is reserved
        if (cowl_vocab_is_reserved_prefix(prefix)) return COWL_ERR;
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
        set_dirty(map);
        return COWL_OK;
    }

    // Mapping not present
    uhash_key(CowlObjectTable, &table->data, i) = cowl_retain(prefix);
    uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
    set_dirty(map);
    return COWL_OK;
}

cowl_ret cowl_prefix_map_add_raw(CowlPrefixMap *map, UString prefix, UString ns, bool overwrite) {
    CowlTable *table = cowl_prefix_map_get_table(map, false);
    if (!table) return COWL_ERR_MEM;

    CowlString key = cowl_string_init(prefix);

    ulib_uint i;
    ulib_ret const ret = uhash_put(CowlObjectTable, &table->data, &key, &i);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);

    if (ret == ULIB_NO) {
        if (!overwrite) return COWL_OK;
        // Mapping present, overwrite mapped namespace unless the prefix is reserved
        if (cowl_vocab_is_reserved_prefix_raw(prefix)) return COWL_ERR;
        CowlString *ns_str = cowl_string_opt(ns, COWL_SO_COPY | COWL_SO_INTERN);
        if (!ns_str) goto oom;
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = ns_str;
        set_dirty(map);
        return COWL_OK;
    }

    // Mapping not present
    CowlString *prefix_str = cowl_string_opt(prefix, COWL_SO_COPY);
    if (!prefix_str) goto oom;

    CowlString *ns_str = cowl_string_opt(ns, COWL_SO_COPY | COWL_SO_INTERN);
    if (!ns_str) {
        cowl_release(prefix_str);
        goto oom;
    }

    uhash_key(CowlObjectTable, &table->data, i) = prefix_str;
    uhash_value(CowlObjectTable, &table->data, i) = ns_str;
    set_dirty(map);
    return COWL_OK;

oom:
    uhash_delete(CowlObjectTable, &table->data, i);
    return COWL_ERR_MEM;
}

cowl_ret cowl_prefix_map_remove_prefix(CowlPrefixMap *map, CowlString *prefix) {
    if (cowl_vocab_is_reserved_prefix(prefix)) return COWL_ERR;

    CowlTable *table = cowl_prefix_map_get_table(map, false);
    CowlAny *ex_key;
    CowlAny *ex_value;

    if (uhmap_pop(CowlObjectTable, &table->data, prefix, &ex_key, &ex_value)) {
        table = cowl_prefix_map_get_table(map, true);
        uhmap_remove(CowlObjectTable, &table->data, ex_value);
        cowl_release(ex_key);
        cowl_release(ex_value);
    }

    return COWL_OK;
}

cowl_ret cowl_prefix_map_remove_ns(CowlPrefixMap *map, CowlString *ns) {
    if (cowl_vocab_is_reserved_ns(ns)) return COWL_ERR;

    CowlTable *table = cowl_prefix_map_get_table(map, true);
    CowlAny *ex_key;
    CowlAny *ex_value;

    if (uhmap_pop(CowlObjectTable, &table->data, ns, &ex_key, &ex_value)) {
        table = cowl_prefix_map_get_table(map, false);
        uhmap_remove(CowlObjectTable, &table->data, ex_value);
        cowl_release(ex_key);
        cowl_release(ex_value);
    }

    return COWL_OK;
}

cowl_ret cowl_prefix_map_merge(CowlPrefixMap *dst, CowlPrefixMap *src, bool overwrite) {
    CowlTable *table = cowl_prefix_map_get_table(src, false);
    cowl_table_foreach (table, e) {
        if (cowl_vocab_is_reserved_prefix(*e.key)) continue;
        cowl_ret ret = cowl_prefix_map_add(dst, *e.key, *e.val, overwrite);
        if (ret) return ret;
    }
    return COWL_OK;
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
