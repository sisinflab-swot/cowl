/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri.h"
#include "cowl_string_private.h"
#include "cowl_sym_table_private.h"
#include "cowl_table_private.h"

static ulib_uint string_hash(void *string) {
    return cowl_string_hash(string);
}

static bool string_equals(void *lhs, void *rhs) {
    return cowl_string_equals(lhs, rhs);
}

static cowl_ret cowl_update_reverse_map(CowlSymTable *st) {
    if (!st->dirty) return COWL_OK;

    CowlTable *h1 = st->prefix_ns_map, *h2 = st->ns_prefix_map;
    cowl_table_foreach (h1, e) {
        if (uhmap_set(CowlObjectTable, &h2->data, *e.val, *e.key, NULL) == UHASH_ERR) {
            return COWL_ERR_MEM;
        }
    }

    st->dirty = false;
    return COWL_OK;
}

CowlSymTable cowl_sym_table_init(void) {
    return (CowlSymTable){ 0 };
}

void cowl_sym_table_deinit(CowlSymTable *st) {
    cowl_table_release_ex(st->prefix_ns_map, true);
    cowl_table_release_ex(st->ns_prefix_map, false);
}

CowlTable *cowl_sym_table_get_prefix_ns_map(CowlSymTable *st, bool reverse) {
    CowlTable **table = reverse ? &st->ns_prefix_map : &st->prefix_ns_map;

    if (!*table) {
        UHash(CowlObjectTable) temp = uhmap_pi(CowlObjectTable, string_hash, string_equals);
        if (!(*table = cowl_table(&temp))) return NULL;
    }

    if (reverse && cowl_update_reverse_map(st)) {
        return NULL;
    }

    return *table;
}

CowlString *cowl_sym_table_get_ns(CowlSymTable *st, CowlString *prefix) {
    return cowl_table_get_value(cowl_sym_table_get_prefix_ns_map(st, false), prefix);
}

CowlString *cowl_sym_table_get_prefix(CowlSymTable *st, CowlString *ns) {
    return cowl_table_get_value(cowl_sym_table_get_prefix_ns_map(st, true), ns);
}

cowl_ret cowl_sym_table_register_prefix(CowlSymTable *st, CowlString *prefix, CowlString *ns,
                                        bool overwrite) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(st, false);
    if (!(table && (ns = cowl_string_intern(ns)))) return COWL_ERR_MEM;

    ulib_uint i;
    uhash_ret ret = uhash_put(CowlObjectTable, &table->data, prefix, &i);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_PRESENT) {
        if (!overwrite) return COWL_OK;
        // Mapping present, overwrite mapped namespace
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
        st->dirty = true;
        return COWL_OK;
    }

    // Mapping not present
    uhash_key(CowlObjectTable, &table->data, i) = cowl_retain(prefix);
    uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
    st->dirty = true;
    return COWL_OK;
}

cowl_ret
cowl_sym_table_register_prefix_raw(CowlSymTable *st, UString prefix, UString ns, bool overwrite) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(st, false);
    if (!table) return COWL_ERR_MEM;

    CowlString key = cowl_string_init(prefix);

    ulib_uint i;
    uhash_ret ret = uhash_put(CowlObjectTable, &table->data, &key, &i);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_PRESENT) {
        if (!overwrite) return COWL_OK;
        // Mapping present, overwrite mapped namespace
        CowlString *ns_str = cowl_string_opt(ns, COWL_SO_COPY | COWL_SO_INTERN);
        if (!ns_str) goto oom;
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = ns_str;
        st->dirty = true;
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
    st->dirty = true;
    return COWL_OK;

oom:
    uhash_delete(CowlObjectTable, &table->data, i);
    return COWL_ERR_MEM;
}

cowl_ret cowl_sym_table_unregister_prefix(CowlSymTable *st, CowlString *prefix) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(st, false);
    CowlAny *ex_key, *ex_value;

    if (uhmap_pop(CowlObjectTable, &table->data, prefix, &ex_key, &ex_value)) {
        table = cowl_sym_table_get_prefix_ns_map(st, true);
        uhmap_remove(CowlObjectTable, &table->data, ex_value);
        cowl_release(ex_key);
        cowl_release(ex_value);
    }

    return COWL_OK;
}

cowl_ret cowl_sym_table_unregister_ns(CowlSymTable *st, CowlString *ns) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(st, true);
    CowlAny *ex_key, *ex_value;

    if (uhmap_pop(CowlObjectTable, &table->data, ns, &ex_key, &ex_value)) {
        table = cowl_sym_table_get_prefix_ns_map(st, false);
        uhmap_remove(CowlObjectTable, &table->data, ex_value);
        cowl_release(ex_key);
        cowl_release(ex_value);
    }

    return COWL_OK;
}

cowl_ret cowl_sym_table_merge(CowlSymTable *st, CowlSymTable *other, bool overwrite) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(other, false);
    cowl_table_foreach (table, e) {
        cowl_ret ret = cowl_sym_table_register_prefix(st, *e.key, *e.val, overwrite);
        if (ret) return ret;
    }
    return COWL_OK;
}

CowlIRI *cowl_sym_table_get_full_iri(CowlSymTable *st, UString ns, UString rem) {
    CowlString ns_local = cowl_string_init(ns);
    CowlString *ns_str = cowl_sym_table_get_ns(st, &ns_local);
    if (!ns_str) return NULL;

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string_opt(rem, COWL_SO_COPY) : cowl_string_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri(ns_str, rem_str);
    cowl_release(rem_str);
    return iri;
}

CowlIRI *cowl_sym_table_parse_full_iri(CowlSymTable *st, UString short_iri) {
    char const *str = ustring_data(short_iri);
    ulib_uint const str_length = ustring_length(short_iri);
    ulib_uint const ns_length = ustring_index_of(short_iri, ':');

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length + 1, str_length - (ns_length + 1));
    return cowl_sym_table_get_full_iri(st, ns, rem);
}
