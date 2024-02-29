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
#include "cowl_vocab.h"

static inline bool cowl_sym_table_is_dirty(CowlSymTable *st) {
    return cowl_object_bit_get(st);
}

static inline void cowl_sym_table_set_dirty(CowlSymTable *st) {
    cowl_object_bit_set(st);
}

static inline void cowl_sym_table_set_clean(CowlSymTable *st) {
    cowl_object_bit_unset(st);
}

static cowl_ret cowl_update_reverse_map(CowlSymTable *st) {
    if (!cowl_sym_table_is_dirty(st)) return COWL_OK;

    CowlTable *h1 = st->prefix_ns_map, *h2 = st->ns_prefix_map;
    cowl_table_foreach (h1, e) {
        if (uhmap_set(CowlObjectTable, &h2->data, *e.val, *e.key, NULL) == UHASH_ERR) {
            return COWL_ERR_MEM;
        }
    }

    cowl_sym_table_set_clean(st);
    return COWL_OK;
}

static inline cowl_ret cowl_sym_table_register_reserved(CowlSymTable *st) {
    CowlVocab const *v = cowl_vocab();
    if (cowl_sym_table_register_prefix(st, v->owl->prefix, v->owl->ns, false) ||
        cowl_sym_table_register_prefix(st, v->rdf->prefix, v->rdf->ns, false) ||
        cowl_sym_table_register_prefix(st, v->rdfs->prefix, v->rdfs->ns, false) ||
        cowl_sym_table_register_prefix(st, v->xsd->prefix, v->xsd->ns, false)) {
        return COWL_ERR_MEM;
    }
    return COWL_OK;
}

CowlSymTable *cowl_sym_table(void) {
    CowlSymTable *st = ulib_alloc(st);
    if (!st) return NULL;
    *st = (CowlSymTable){ .super = COWL_OBJECT_INIT(COWL_OT_SYM_TABLE) };

    if (cowl_sym_table_register_reserved(st)) {
        cowl_sym_table_free(st);
        st = NULL;
    }

    return st;
}

void cowl_sym_table_free(CowlSymTable *st) {
    cowl_table_release_ex(st->prefix_ns_map, true);
    cowl_table_release_ex(st->ns_prefix_map, false);
    ulib_free(st);
}

CowlTable *cowl_sym_table_get_prefix_ns_map(CowlSymTable *st, bool reverse) {
    CowlTable **table = reverse ? &st->ns_prefix_map : &st->prefix_ns_map;

    if (!*table) {
        UHash(CowlObjectTable) temp = cowl_string_map();
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
        // Mapping present, overwrite mapped namespace unless the prefix is reserved
        if (cowl_vocab_is_reserved_prefix(prefix)) return COWL_ERR;
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
        cowl_sym_table_set_dirty(st);
        return COWL_OK;
    }

    // Mapping not present
    uhash_key(CowlObjectTable, &table->data, i) = cowl_retain(prefix);
    uhash_value(CowlObjectTable, &table->data, i) = cowl_retain(ns);
    cowl_sym_table_set_dirty(st);
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
        // Mapping present, overwrite mapped namespace unless the prefix is reserved
        if (cowl_vocab_is_reserved_prefix_raw(prefix)) return COWL_ERR;
        CowlString *ns_str = cowl_string_opt(ns, COWL_SO_COPY | COWL_SO_INTERN);
        if (!ns_str) goto oom;
        cowl_release(uhash_value(CowlObjectTable, &table->data, i));
        uhash_value(CowlObjectTable, &table->data, i) = ns_str;
        cowl_sym_table_set_dirty(st);
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
    cowl_sym_table_set_dirty(st);
    return COWL_OK;

oom:
    uhash_delete(CowlObjectTable, &table->data, i);
    return COWL_ERR_MEM;
}

cowl_ret cowl_sym_table_unregister_prefix(CowlSymTable *st, CowlString *prefix) {
    if (cowl_vocab_is_reserved_prefix(prefix)) return COWL_ERR;

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
    if (cowl_vocab_is_reserved_ns(ns)) return COWL_ERR;

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
        if (cowl_vocab_is_reserved_prefix(*e.key)) continue;
        cowl_ret ret = cowl_sym_table_register_prefix(st, *e.key, *e.val, overwrite);
        if (ret) return ret;
    }
    return COWL_OK;
}

CowlIRI *cowl_sym_table_get_iri(CowlSymTable *st, UString prefix, UString rem) {
    CowlString prefix_local = cowl_string_init(prefix);
    CowlString *prefix_str = cowl_sym_table_get_ns(st, &prefix_local);
    if (!prefix_str) return NULL;

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string_opt(rem, COWL_SO_COPY) : cowl_string_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri(prefix_str, rem_str);
    cowl_release(rem_str);
    return iri;
}

CowlIRI *cowl_sym_table_parse_short_iri(CowlSymTable *st, UString short_iri) {
    char const *str = ustring_data(short_iri);
    ulib_uint const str_length = ustring_length(short_iri);
    ulib_uint const ns_length = ustring_index_of(short_iri, ':');

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length + 1, str_length - (ns_length + 1));
    return cowl_sym_table_get_iri(st, ns, rem);
}

CowlIRI *cowl_sym_table_parse_iri(CowlSymTable *st, UString str) {
    CowlIRI *iri = cowl_sym_table_parse_short_iri(st, str);
    return iri ? iri : cowl_iri_from_string(str);
}
