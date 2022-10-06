/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sym_table_private.h"
#include "cowl_anon_ind_private.h"
#include "cowl_iri.h"
#include "cowl_ontology.h"
#include "cowl_string_private.h"
#include "cowl_table_private.h"

static ulib_uint ptr_hash(void *ptr) { return uhash_ptr_hash(ptr); }
static bool ptr_equals(void *lhs, void *rhs) { return lhs == rhs; }

static ulib_uint string_hash(void *string) { return cowl_string_hash(string); }
static bool string_equals(void *lhs, void *rhs) { return cowl_string_equals(lhs, rhs); }

static ulib_uint onto_hash(void *onto) { return cowl_ontology_hash(onto); }
static bool onto_equals(void *lhs, void *rhs) { return cowl_ontology_equals(lhs, rhs); }

static cowl_ret cowl_update_reverse_map(CowlTable *h1, CowlTable *h2) {
    if (cowl_table_count(h1) == cowl_table_count(h2)) return COWL_OK;

    cowl_table_foreach(h1, e) {
        if (uhmap_add(CowlObjectTable, &h2->data, *e.val, *e.key, NULL) == UHASH_ERR) {
            return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}

CowlSymTable cowl_sym_table_init(void) {
    return (CowlSymTable){0};
}

void cowl_sym_table_deinit(CowlSymTable *st) {
    cowl_table_release(st->import_onto_map);
    cowl_table_release_ex(st->onto_import_map, false);
    cowl_table_release(st->prefix_ns_map);
    cowl_table_release_ex(st->ns_prefix_map, false);
    cowl_table_release(st->id_anon_map);
    cowl_table_release_ex(st->anon_id_map, false);
}

CowlTable* cowl_sym_table_get_iri_onto_map(CowlSymTable *st, bool reverse) {
    CowlTable **table = reverse ? &st->onto_import_map : &st->import_onto_map;

    if (!*table) {
        UHash(CowlObjectTable) temp;

        if (reverse) {
            temp = uhmap_pi(CowlObjectTable, onto_hash, onto_equals);
        } else {
            temp = uhmap_pi(CowlObjectTable, ptr_hash, ptr_equals);
        }

        if (!(*table = cowl_table(&temp))) return NULL;
    }

    if (reverse && cowl_update_reverse_map(st->import_onto_map, st->onto_import_map)) {
        return NULL;
    }

    return *table;
}

CowlIRI* cowl_sym_table_get_import_iri(CowlSymTable *st, CowlOntology *ontology) {
    return cowl_table_get_value(cowl_sym_table_get_iri_onto_map(st, true), ontology);
}

CowlOntology* cowl_sym_table_get_onto_for_import_iri(CowlSymTable *st, CowlIRI *import) {
    return cowl_table_get_value(cowl_sym_table_get_iri_onto_map(st, false), import);
}

cowl_ret cowl_sym_table_add_import(CowlSymTable *st, CowlIRI *iri, CowlOntology *import) {
    CowlTable *table = cowl_sym_table_get_iri_onto_map(st, false);
    if (!table) return COWL_ERR_MEM;

    UHash(CowlObjectTable) *tbl = &table->data;
    uhash_ret ret = uhmap_add(CowlObjectTable, tbl, iri, import, NULL);

    if (ret == UHASH_PRESENT) return COWL_ERR_IMPORT;
    if (ret == UHASH_INSERTED) {
        cowl_iri_retain(iri);
        if (import) cowl_ontology_retain(import);
        return COWL_OK;
    }

    return COWL_ERR_MEM;
}

cowl_ret cowl_sym_table_remove_import(CowlSymTable *st, CowlIRI *iri) {
    CowlTable *table = st->import_onto_map;
    if (!table) return COWL_OK;

    void *import = NULL;
    if (!uhmap_pop(CowlObjectTable, &table->data, iri, NULL, &import)) return COWL_OK;
    cowl_iri_release(iri);

    if (import) {
        if (st->onto_import_map) uhmap_remove(CowlObjectTable, &st->onto_import_map->data, import);
        cowl_ontology_release(import);
    }

    return COWL_OK;
}

CowlTable* cowl_sym_table_get_prefix_ns_map(CowlSymTable *st, bool reverse) {
    CowlTable **table = reverse ? &st->ns_prefix_map : &st->prefix_ns_map;

    if (!*table) {
        UHash(CowlObjectTable) temp = uhmap_pi(CowlObjectTable, string_hash, string_equals);
        if (!(*table = cowl_table(&temp))) return NULL;
    }

    if (reverse && cowl_update_reverse_map(st->prefix_ns_map, st->ns_prefix_map)) {
        return NULL;
    }

    return *table;
}

CowlString* cowl_sym_table_get_ns(CowlSymTable *st, CowlString *prefix) {
    return cowl_table_get_value(cowl_sym_table_get_prefix_ns_map(st, false), prefix);
}

CowlString* cowl_sym_table_get_prefix(CowlSymTable *st, CowlString *ns) {
    return cowl_table_get_value(cowl_sym_table_get_prefix_ns_map(st, true), ns);
}

cowl_ret cowl_sym_table_register_prefix(CowlSymTable *st, CowlString *prefix, CowlString *ns) {
    CowlTable *table = cowl_sym_table_get_prefix_ns_map(st, false);
    if (!table) return COWL_ERR_MEM;

    uhash_ret ret = uhmap_add(CowlObjectTable, &table->data, prefix, ns, NULL);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }

    return COWL_OK;
}

CowlIRI* cowl_sym_table_get_full_iri(CowlSymTable *st, UString ns, UString rem) {
    CowlString ns_local = cowl_string_init(ns);
    CowlString *ns_str = cowl_sym_table_get_ns(st, &ns_local);
    if (!ns_str) return NULL;

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string(ustring_dup(rem)) : cowl_string_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri(ns_str, rem_str);
    cowl_string_release(rem_str);
    return iri;
}

CowlIRI* cowl_sym_table_parse_full_iri(CowlSymTable *st, UString short_iri) {
    char const *str = ustring_data(short_iri);
    ulib_uint const str_length = ustring_length(short_iri);
    ulib_uint const ns_length = ustring_index_of(short_iri, ':');

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length + 1, str_length - (ns_length + 1));
    return cowl_sym_table_get_full_iri(st, ns, rem);
}

CowlTable* cowl_sym_table_get_name_anon_map(CowlSymTable *st, bool reverse) {
    CowlTable **table = reverse ? &st->anon_id_map : &st->id_anon_map;

    if (!*table) {
        UHash(CowlObjectTable) temp;

        if (reverse) {
            temp = uhmap_pi(CowlObjectTable, ptr_hash, ptr_equals);
        } else {
            temp = uhmap_pi(CowlObjectTable, string_hash, string_equals);
        }

        if (!(*table = cowl_table(&temp))) return NULL;
    }

    if (reverse && cowl_update_reverse_map(st->id_anon_map, st->anon_id_map)) {
        return NULL;
    }

    return *table;
}

CowlAnonInd* cowl_sym_table_get_anon(CowlSymTable *st, UString id) {
    CowlTable *table = cowl_sym_table_get_name_anon_map(st, false);
    if (!table) return NULL;

    ulib_uint idx;
    CowlString id_str = cowl_string_init(id);
    UHash(CowlObjectTable) *id_anon_map = &table->data;
    uhash_ret ret = uhash_put(CowlObjectTable, id_anon_map, &id_str, &idx);

    CowlAnonInd *ind = NULL;

    if (ret == UHASH_INSERTED) {
        CowlString *string = cowl_string_copy(&id_str);
        ind = cowl_anon_ind();

        if (string && ind) {
            uhash_key(CowlObjectTable, id_anon_map, idx) = string;
            uhash_value(CowlObjectTable, id_anon_map, idx) = ind;
        } else {
            uhash_delete(CowlObjectTable, id_anon_map, idx);
            cowl_string_release(string);
            cowl_anon_ind_release(ind);
            ind = NULL;
        }
    } else if (ret == UHASH_PRESENT) {
        ind = uhash_value(CowlObjectTable, id_anon_map, idx);
    }

    return ind;
}

static CowlString* cowl_sym_table_generate_id(CowlSymTable *st, CowlAnonInd *ind) {
    CowlTable *table = cowl_sym_table_get_name_anon_map(st, false);
    if (!table) return NULL;

    UString id = cowl_anon_ind_generate_id();
    if (ustring_is_null(id)) return NULL;
    CowlString id_str = cowl_string_init(id);

    UHash(CowlObjectTable) *id_anon_map = &table->data;
    ulib_uint i;
    uhash_ret ret;

    while ((ret = uhash_put(CowlObjectTable, id_anon_map, &id_str, &i)) == UHASH_PRESENT) {
        ustring_deinit(&id);
        id = cowl_anon_ind_generate_id();
        if (ustring_is_null(id)) return NULL;
        id_str = cowl_string_init(id);
    }

    if (ret == UHASH_ERR) {
        ustring_deinit(&id);
        return NULL;
    }

    CowlString *key = cowl_string(id);
    if (!key) {
        uhash_delete(CowlObjectTable, id_anon_map, i);
        return NULL;
    }

    uhash_key(CowlObjectTable, id_anon_map, i) = key;
    uhash_value(CowlObjectTable, id_anon_map, i) = ind;

    return key;
}

CowlString* cowl_sym_table_get_name_for_anon(CowlSymTable *st, CowlAnonInd *ind) {
    CowlTable *table = cowl_sym_table_get_name_anon_map(st, true);
    if (!table) return NULL;

    UHash(CowlObjectTable) *anon_id_map = &table->data;
    ulib_uint i;
    uhash_ret ret = uhash_put(CowlObjectTable, anon_id_map, ind, &i);

    if (ret == UHASH_ERR) return NULL;
    if (ret == UHASH_PRESENT) return uhash_value(CowlObjectTable, anon_id_map, i);

    CowlString *id = cowl_sym_table_generate_id(st, ind);

    if (!id) {
        uhash_delete(CowlObjectTable, anon_id_map, i);
        return NULL;
    }

    uhash_value(CowlObjectTable, anon_id_map, i) = id;
    return id;
}
