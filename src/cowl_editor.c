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

static ulib_uint string_hash(void *string) { return cowl_string_hash(string); }
static bool string_equals(void *lhs, void *rhs) { return cowl_string_equals(lhs, rhs); }

static ulib_uint anon_hash(void *anon) { return cowl_anon_ind_hash(anon); }
static bool anon_equals(void *lhs, void *rhs) { return cowl_anon_ind_equals(lhs, rhs); }

CowlEditor* cowl_editor_alloc(CowlManager *manager) {
    CowlEditor *editor = ulib_alloc(editor);
    if (!editor) goto err;

    *editor = (CowlEditor) { .manager = manager };

    UHash(CowlObjectTable) temp = uhmap_init_pi(CowlObjectTable, string_hash, string_equals);
    editor->prefix_ns_map = cowl_table_get(&temp);
    if (!editor->prefix_ns_map) goto err;

    temp = uhmap_init_pi(CowlObjectTable, string_hash, string_equals);
    editor->ns_prefix_map = cowl_table_get(&temp);
    if (!editor->ns_prefix_map) goto err;

    temp = uhmap_init_pi(CowlObjectTable, string_hash, string_equals);
    editor->id_anon_map = cowl_table_get(&temp);
    if (!editor->id_anon_map) goto err;

    temp = uhmap_init_pi(CowlObjectTable, anon_hash, anon_equals);
    editor->anon_id_map = cowl_table_get(&temp);
    if (!editor->anon_id_map) goto err;

    return editor;

err:
    cowl_editor_free(editor);
    return NULL;
}

void cowl_editor_free(CowlEditor *editor) {
    if (!editor) return;
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

cowl_ret cowl_editor_add_import(CowlEditor *editor, CowlIRI *iri) {
    CowlOntology *import = NULL;
    cowl_ret ret;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto err;
    }

    CowlImportLoader loader = editor->manager->loader;
    if (!loader.load_ontology) loader = cowl_api_get_import_loader();
    if (!loader.load_ontology) return COWL_OK;

    import = loader.load_ontology(loader.ctx, iri);

    if (!import) {
        ret = COWL_ERR_IMPORT;
        goto err;
    }

    ret = cowl_ontology_add_import(editor->ontology, import);
    cowl_ontology_release(import);

err:
    if (ret) cowl_editor_handle_error_type(editor, ret);
    return ret;
}

cowl_ret cowl_editor_add_annot(CowlEditor *editor, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(editor->ontology, annot);
    if (ret) cowl_editor_handle_error_type(editor, ret);
    return ret;
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

static cowl_ret cowl_update_reverse_map(CowlTable *h1, CowlTable *h2) {
    if (cowl_table_count(h1) == cowl_table_count(h2)) return COWL_OK;

    cowl_table_foreach(h1, e) {
        if (uhmap_add(CowlObjectTable, &h2->data, *e.val, *e.key, NULL) == UHASH_ERR) {
            return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}

CowlTable* cowl_editor_get_prefix_ns_map(CowlEditor *editor) {
    return editor->prefix_ns_map;
}

CowlTable* cowl_editor_get_ns_prefix_map(CowlEditor *editor) {
    return editor->ns_prefix_map;
}

CowlString* cowl_editor_get_ns(CowlEditor *editor, CowlString *prefix) {
    return cowl_table_get_value(editor->prefix_ns_map, prefix);
}

CowlString* cowl_editor_get_prefix(CowlEditor *editor, CowlString *ns) {
    if (cowl_update_reverse_map(editor->prefix_ns_map, editor->ns_prefix_map)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
        return NULL;
    }
    return cowl_table_get_value(editor->ns_prefix_map, ns);
}

cowl_ret cowl_editor_register_prefix(CowlEditor *editor, CowlString *prefix, CowlString *ns) {
    uhash_ret ret = uhmap_add(CowlObjectTable, &editor->prefix_ns_map->data, prefix, ns, NULL);

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
        UString comp[] = { ustring_literal("no namespace mapping for "), ns };
        UString err_str = ustring_concat(comp, ulib_array_count(comp));
        cowl_editor_handle_error(editor, COWL_ERR_SYNTAX, err_str);
        ustring_deinit(&err_str);
        return NULL;
    }

    ulib_uint const rem_length = ustring_length(rem);
    CowlString *rem_str = rem_length ? cowl_string_get(ustring_dup(rem)) : cowl_string_get_empty();
    if (!rem_str) return NULL;

    CowlIRI *iri = cowl_iri_get(ns_str, rem_str);
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

CowlTable* cowl_editor_get_name_anon_ind_map(CowlEditor *editor) {
    return editor->id_anon_map;
}

CowlTable* cowl_editor_get_anon_ind_name_map(CowlEditor *editor) {
    return editor->anon_id_map;
}

CowlAnonInd* cowl_editor_get_anon_ind(CowlEditor *editor, UString id) {
    ulib_uint idx;
    CowlString id_str = cowl_string_init(id);
    UHash(CowlObjectTable) *id_anon_map = &editor->id_anon_map->data;
    uhash_ret ret = uhash_put(CowlObjectTable, id_anon_map, &id_str, &idx);

    CowlAnonInd *ind = NULL;

    if (ret == UHASH_INSERTED) {
        CowlString *string = cowl_string_copy(&id_str);
        ind = cowl_anon_ind_get();

        if (string && ind) {
            uhash_key(CowlObjectTable, id_anon_map, idx) = string;
            uhash_value(CowlObjectTable, id_anon_map, idx) = cowl_anon_ind_retain(ind);
        } else {
            uhash_delete(CowlObjectTable, id_anon_map, idx);
            cowl_string_release(string);
            cowl_anon_ind_release(ind);
            ind = NULL;
        }
    } else if (ret == UHASH_PRESENT) {
        ind = uhash_value(CowlObjectTable, id_anon_map, idx);
        cowl_anon_ind_retain(ind);
    }

    return ind;
}

static CowlString* cowl_editor_generate_id(CowlEditor *editor, CowlAnonInd *ind) {
    UString id = cowl_anon_ind_generate_id();
    if (ustring_is_null(id)) return NULL;
    CowlString id_str = cowl_string_init(id);

    UHash(CowlObjectTable) *id_anon_map = &editor->id_anon_map->data;
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


    CowlString *key = cowl_string_get(id);
    if (!key) {
        uhash_delete(CowlObjectTable, id_anon_map, i);
        return NULL;
    }

    uhash_key(CowlObjectTable, id_anon_map, i) = key;
    uhash_value(CowlObjectTable, id_anon_map, i) = ind;

    return key;
}

CowlString* cowl_editor_get_id_for_anon_ind(CowlEditor *editor, CowlAnonInd *ind) {
    if (cowl_update_reverse_map(editor->id_anon_map, editor->anon_id_map)) goto err;

    UHash(CowlObjectTable) *anon_id_map = &editor->anon_id_map->data;
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
    cowl_anon_ind_retain(ind);
    return id;

err:
    cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
    return NULL;
}

void cowl_editor_handle_error(CowlEditor *editor, cowl_ret code, UString description) {
    CowlManager *manager = editor->manager;
    CowlErrorHandler handler = manager->handler;
    if (!handler.handle_error) handler = cowl_api_get_error_handler();
    if (!handler.handle_error) return;

    UString temp = ustring_is_null(editor->description) ? ustring_empty : editor->description;
    CowlString source = cowl_string_init(temp);
    CowlString descr = cowl_string_init(description);
    CowlReader reader = cowl_manager_get_reader(manager);

    CowlError error = {
        .code = code,
        .location = {
            .line = reader.get_line ? reader.get_line(editor->state) : 0,
            .source = cowl_string_get_length(&source) ? &source : NULL,
            .iri = editor->ontology ? cowl_ontology_get_id(editor->ontology).ontology_iri : NULL,
        },
        .origin = (CowlObject *)manager,
        .description = cowl_string_get_length(&descr) ? &descr : NULL
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_editor_handle_error_type(CowlEditor *editor, cowl_ret code) {
    cowl_editor_handle_error(editor, code, cowl_ret_to_ustring(code));
}

void cowl_editor_handle_stream_error(CowlEditor *editor, ustream_ret code) {
    cowl_editor_handle_error_type(editor, cowl_ret_from_ustream(code));
}
