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
#include "cowl_anon_ind.h"
#include "cowl_config_private.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

CowlEditor* cowl_editor_alloc(CowlManager *manager) {
    CowlEditor *editor = ulib_alloc(editor);
    if (!editor) return NULL;
    *editor = (CowlEditor) {
        .manager = manager,
        .prefix_ns_map = uhmap_init(CowlObjectTable),
        .anon_ind_map = uhmap_init(CowlObjectTable)
    };
    return editor;
}

void cowl_editor_free(CowlEditor *editor) {
    if (!editor) return;

    uhash_foreach(CowlObjectTable, &editor->prefix_ns_map, prefix) {
        cowl_string_release(*prefix.key);
        cowl_string_release(*prefix.val);
    }
    uhash_deinit(CowlObjectTable, &editor->prefix_ns_map);

    uhash_foreach(CowlObjectTable, &editor->anon_ind_map, ind) {
        cowl_string_release(*ind.key);
        cowl_anon_ind_release(*ind.val);
    }
    uhash_deinit(CowlObjectTable, &editor->anon_ind_map);

    cowl_ontology_release(editor->ontology);
    ulib_free(editor);
}

CowlOntology* cowl_editor_get_ontology(CowlEditor *editor) {
    return editor->ontology ? cowl_ontology_retain(editor->ontology) : NULL;
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

cowl_ret cowl_editor_register_ns(CowlEditor *editor, CowlString *prefix, CowlString *ns) {
    uhash_ret ret = uhmap_add(CowlObjectTable, &editor->prefix_ns_map, prefix, ns, NULL);

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
    CowlString *ns_str = uhmap_get(CowlObjectTable, &editor->prefix_ns_map, &ns_local, NULL);

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
    ulib_uint const ns_length = ustring_index_of(short_iri, ':') + 1;

    UString ns = ustring_wrap(str, ns_length);
    UString rem = ustring_wrap(str + ns_length, str_length - ns_length);
    return cowl_editor_get_full_iri(editor, ns, rem);
}

CowlAnonInd* cowl_editor_get_anon_ind(CowlEditor *editor, UString id) {
    ulib_uint idx;
    CowlString id_str = cowl_string_init(id);
    uhash_ret ret = uhash_put(CowlObjectTable, &editor->anon_ind_map, &id_str, &idx);

    CowlAnonInd *ind = NULL;

    if (ret == UHASH_INSERTED) {
        CowlString *string = cowl_string_copy(&id_str);
        ind = cowl_anon_ind_get();

        if (string && ind) {
            uhash_key(CowlObjectTable, &editor->anon_ind_map, idx) = string;
            uhash_value(CowlObjectTable, &editor->anon_ind_map, idx) = cowl_anon_ind_retain(ind);
        } else {
            uhash_delete(CowlObjectTable, &editor->anon_ind_map, idx);
            cowl_string_release(string);
            cowl_anon_ind_release(ind);
            ind = NULL;
        }
    } else if (ret == UHASH_PRESENT) {
        ind = uhash_value(CowlObjectTable, &editor->anon_ind_map, idx);
        cowl_anon_ind_retain(ind);
    }

    return ind;
}

void cowl_editor_handle_error(CowlEditor *editor, cowl_ret code, UString description) {
    CowlManager *manager = editor->manager;
    CowlErrorHandler handler = manager->handler;
    if (!handler.handle_error) handler = cowl_api_get_error_handler();
    if (!handler.handle_error) return;

    UString temp = ustring_is_null(editor->description) ? ustring_empty : editor->description;
    CowlString source = cowl_string_init(temp);
    CowlString descr = cowl_string_init(description);
    CowlParser parser = cowl_manager_get_parser(manager);

    CowlError error = {
        .code = code,
        .location = {
            .line = parser.get_line ? parser.get_line(editor->state) : 0,
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
