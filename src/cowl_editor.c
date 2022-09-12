/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_editor_private.h"
#include "cowl_anon_ind_private.h"
#include "cowl_config_private.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"
#include "cowl_table_private.h"

static ulib_uint ptr_hash(void *ptr) { return uhash_ptr_hash(ptr); }
static bool ptr_equals(void *lhs, void *rhs) { return lhs == rhs; }

static ulib_uint string_hash(void *string) { return cowl_string_hash(string); }
static bool string_equals(void *lhs, void *rhs) { return cowl_string_equals(lhs, rhs); }

static ulib_uint onto_hash(void *onto) { return cowl_ontology_hash(onto); }
static bool onto_equals(void *lhs, void *rhs) { return cowl_ontology_equals(lhs, rhs); }

CowlEditor* cowl_editor_alloc(CowlManager *manager) {
    CowlEditor *editor = ulib_alloc(editor);
    if (!editor) return NULL;
    *editor = (CowlEditor) { .manager = manager };
    return editor;
}

void cowl_editor_free(CowlEditor *editor) {
    if (!editor) return;
    cowl_table_release(editor->onto_import_map);
    cowl_table_release_ex(editor->import_onto_map, false);
    cowl_table_release(editor->prefix_ns_map);
    cowl_table_release_ex(editor->ns_prefix_map, false);
    cowl_table_release(editor->id_anon_map);
    cowl_table_release_ex(editor->anon_id_map, false);
    cowl_ontology_release(editor->ontology);
    ulib_free(editor);
}

CowlOntology* cowl_editor_get_ontology(CowlEditor *editor) {
    return editor->ontology;
}

void cowl_editor_set_ontology(CowlEditor *editor, CowlOntology *ontology) {
    if (editor->ontology) cowl_ontology_release(editor->ontology);
    editor->ontology = cowl_ontology_retain(ontology);
}

void cowl_editor_set_iri(CowlEditor *editor, CowlIRI *iri) {
    cowl_ontology_set_iri(editor->ontology, iri);
}

void cowl_editor_set_version(CowlEditor *editor, CowlIRI *version) {
    cowl_ontology_set_version(editor->ontology, version);
}

cowl_ret cowl_editor_add_annot(CowlEditor *editor, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(editor->ontology, annot);
    if (ret) cowl_editor_handle_error_type(editor, ret);
    return ret;
}

cowl_ret cowl_editor_remove_annot(CowlEditor *editor, CowlAnnotation *annot) {
    cowl_ontology_remove_annot(editor->ontology, annot);
    return COWL_OK;
}

cowl_ret cowl_editor_add_import(CowlEditor *editor, CowlIRI *iri) {
    cowl_ret ret = COWL_OK;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    CowlOntology *import = NULL;
    CowlImportLoader loader = editor->manager->loader;
    if (!loader.load_ontology) loader = cowl_get_import_loader();

    if (loader.load_ontology) {
        if ((import = loader.load_ontology(loader.ctx, iri))) {
            ret = cowl_ontology_add_import(editor->ontology, import);
            cowl_ontology_release(import);
        } else {
            ret = COWL_ERR_IMPORT;
        }
    }

    if (!import) goto end;

    CowlTable *table = cowl_editor_get_onto_import_iri_map(editor, false);
    if (!table) {
        ret = COWL_ERR_MEM;
        goto end;
    }

    uhash_ret lret = uhmap_add(CowlObjectTable, &table->data, import, iri, NULL);
    if (lret == UHASH_ERR) {
        ret = COWL_ERR_MEM;
    } else if (lret == UHASH_INSERTED) {
        cowl_ontology_retain(import);
        cowl_iri_retain(iri);
    }

end:
    if (ret) cowl_editor_handle_error_type(editor, ret);
    return ret;
}

cowl_ret cowl_editor_remove_import(CowlEditor *editor, CowlIRI *iri) {
    if (!editor->onto_import_map) return COWL_OK;

    CowlTable *table = cowl_editor_get_onto_import_iri_map(editor, true);
    if (!table) return COWL_ERR_MEM;

    void *import = NULL;
    uhmap_pop(CowlObjectTable, &table->data, iri, NULL, &import);
    cowl_iri_release(iri);
    if (!import) return COWL_OK;

    uhmap_remove(CowlObjectTable, &editor->onto_import_map->data, import);
    cowl_ontology_remove_import(editor->ontology, import);
    cowl_ontology_release(import);

    return COWL_OK;
}

cowl_ret cowl_editor_add_axiom(CowlEditor *editor, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = cowl_ontology_add_axiom(editor->ontology, axiom);

    if (ret) {
        cowl_editor_handle_error_type(editor, ret);
        return ret;
    }

    return COWL_OK;
}

cowl_ret cowl_editor_remove_axiom(CowlEditor *editor, CowlAxiom *axiom) {
    cowl_ontology_remove_axiom(editor->ontology, axiom);
    return COWL_OK;
}

static cowl_ret cowl_editor_create_map(CowlEditor *editor, CowlTable **map,
                                       UHash(CowlObjectTable) *table) {
    *map = cowl_table(table);
    if (*map) return COWL_OK;
    cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
    uhash_deinit(CowlObjectTable, table);
    return COWL_ERR_MEM;
}

static cowl_ret cowl_update_reverse_map(CowlTable *h1, CowlTable *h2) {
    if (cowl_table_count(h1) == cowl_table_count(h2)) return COWL_OK;

    cowl_table_foreach(h1, e) {
        if (uhmap_add(CowlObjectTable, &h2->data, *e.val, *e.key, NULL) == UHASH_ERR) {
            return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}

CowlTable* cowl_editor_get_onto_import_iri_map(CowlEditor *editor, bool reverse) {
    CowlTable **table = reverse ? &editor->import_onto_map : &editor->onto_import_map;

    if (!*table) {
        UHash(CowlObjectTable) temp;

        if (reverse) {
            temp = uhmap_pi(CowlObjectTable, ptr_hash, ptr_equals);
        } else {
            temp = uhmap_pi(CowlObjectTable, onto_hash, onto_equals);
        }

        if (cowl_editor_create_map(editor, table, &temp)) return NULL;
    }

    if (reverse && cowl_update_reverse_map(editor->onto_import_map, editor->import_onto_map)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    return *table;
}

CowlIRI* cowl_editor_get_import_iri(CowlEditor *editor, CowlOntology *ontology) {
    return cowl_table_get_value(editor->onto_import_map, ontology);
}

CowlOntology* cowl_editor_get_onto_for_import_iri(CowlEditor *editor, CowlIRI *import) {
    return cowl_table_get_value(cowl_editor_get_onto_import_iri_map(editor, true), import);
}

CowlTable* cowl_editor_get_prefix_ns_map(CowlEditor *editor, bool reverse) {
    CowlTable **table = reverse ? &editor->ns_prefix_map : &editor->prefix_ns_map;

    if (!*table) {
        UHash(CowlObjectTable) temp = uhmap_pi(CowlObjectTable, string_hash, string_equals);
        if (cowl_editor_create_map(editor, table, &temp)) return NULL;
    }

    if (reverse && cowl_update_reverse_map(editor->prefix_ns_map, editor->ns_prefix_map)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    return *table;
}

CowlString* cowl_editor_get_ns(CowlEditor *editor, CowlString *prefix) {
    return cowl_table_get_value(editor->prefix_ns_map, prefix);
}

CowlString* cowl_editor_get_prefix(CowlEditor *editor, CowlString *ns) {
    return cowl_table_get_value(cowl_editor_get_prefix_ns_map(editor, true), ns);
}

cowl_ret cowl_editor_register_prefix(CowlEditor *editor, CowlString *prefix, CowlString *ns) {
    CowlTable *table = cowl_editor_get_prefix_ns_map(editor, false);
    if (!table) return COWL_ERR_MEM;

    uhash_ret ret = uhmap_add(CowlObjectTable, &table->data, prefix, ns, NULL);

    if (ret == UHASH_ERR) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    if (ret == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }

    return COWL_OK;
}

CowlIRI* cowl_editor_get_full_iri(CowlEditor *editor, UString ns, UString rem) {
    CowlString ns_local = cowl_string_init(ns);
    CowlString *ns_str = cowl_table_get_value(editor->prefix_ns_map, &ns_local);

    if (!ns_str) {
        // We couldn't find a namespace mapping for the specified short namespace.
        UString comp[] = {
            ustring_literal("no namespace mapping for \""), ns , ustring_literal("\"")
        };
        UString err_str = ustring_concat(comp, ulib_array_count(comp));
        cowl_editor_handle_error(editor, COWL_ERR, err_str);
        ustring_deinit(&err_str);
        return NULL;
    }

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string(ustring_dup(rem)) : cowl_string_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri(ns_str, rem_str);
    cowl_string_release(rem_str);
    return iri;
}

CowlIRI* cowl_editor_parse_full_iri(CowlEditor *editor, UString short_iri) {
    char const *str = ustring_data(short_iri);
    ulib_uint const str_length = ustring_length(short_iri);
    ulib_uint const ns_length = ustring_index_of(short_iri, ':');

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length + 1, str_length - (ns_length + 1));
    return cowl_editor_get_full_iri(editor, ns, rem);
}

CowlTable* cowl_editor_get_name_anon_ind_map(CowlEditor *editor, bool reverse) {
    CowlTable **table = reverse ? &editor->anon_id_map : &editor->id_anon_map;

    if (!*table) {
        UHash(CowlObjectTable) temp;

        if (reverse) {
            temp = uhmap_pi(CowlObjectTable, ptr_hash, ptr_equals);
        } else {
            temp = uhmap_pi(CowlObjectTable, string_hash, string_equals);
        }

        if (cowl_editor_create_map(editor, table, &temp)) return NULL;
    }

    if (reverse && cowl_update_reverse_map(editor->id_anon_map, editor->anon_id_map)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }

    return *table;
}

CowlAnonInd* cowl_editor_get_anon_ind(CowlEditor *editor, UString id) {
    CowlTable *table = cowl_editor_get_name_anon_ind_map(editor, false);
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

static CowlString* cowl_editor_generate_id(CowlEditor *editor, CowlAnonInd *ind) {
    CowlTable *table = cowl_editor_get_name_anon_ind_map(editor, false);
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

CowlString* cowl_editor_get_name_for_anon_ind(CowlEditor *editor, CowlAnonInd *ind) {
    CowlTable *table = cowl_editor_get_name_anon_ind_map(editor, true);
    if (!table) goto err;

    UHash(CowlObjectTable) *anon_id_map = &table->data;
    ulib_uint i;
    uhash_ret ret = uhash_put(CowlObjectTable, anon_id_map, ind, &i);

    if (ret == UHASH_ERR) goto err;
    if (ret == UHASH_PRESENT) return uhash_value(CowlObjectTable, anon_id_map, i);

    CowlString *id = cowl_editor_generate_id(editor, ind);

    if (!id) {
        uhash_delete(CowlObjectTable, anon_id_map, i);
        goto err;
    }

    uhash_value(CowlObjectTable, anon_id_map, i) = id;
    return id;

err:
    cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
    return NULL;
}

static void cowl_handle_error(CowlEditor *editor, cowl_ret code, ulib_uint line, UString desc) {
    CowlManager *manager = editor->manager;
    CowlErrorHandler handler = manager->handler;
    if (!handler.handle_error) handler = cowl_get_error_handler();
    if (!handler.handle_error) return;

    UString temp = ustring_is_null(editor->description) ? ustring_empty : editor->description;
    CowlString source = cowl_string_init(temp);
    CowlString description = cowl_string_init(desc);

    CowlError error = {
        .code = code,
        .location = {
            .line = line,
            .source = cowl_string_get_length(&source) ? &source : NULL,
            .iri = editor->ontology ? cowl_ontology_get_id(editor->ontology).iri : NULL,
        },
        .origin = (CowlObject *)manager,
        .description = cowl_string_get_length(&description) ? &description : NULL
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_editor_handle_error(CowlEditor *editor, cowl_ret code, UString description) {
    cowl_handle_error(editor, code, 0, description);
}

void cowl_editor_handle_error_type(CowlEditor *editor, cowl_ret code) {
    cowl_editor_handle_error(editor, code, cowl_ret_to_ustring(code));
}

void cowl_editor_handle_syntax_error(CowlEditor *editor, ulib_uint line, UString description) {
    if (ustring_is_empty(description)) description = cowl_ret_to_ustring(COWL_ERR_SYNTAX);
    cowl_handle_error(editor, COWL_ERR_SYNTAX, line, description);
}

void cowl_editor_handle_stream_error(CowlEditor *editor, ustream_ret code) {
    cowl_editor_handle_error_type(editor, cowl_ret_from_ustream(code));
}
