/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_change_handler.h"
#include "cowl_any.h"
#include "cowl_iterator.h"
#include "cowl_ontology.h"
#include "cowl_prefix_map.h"
#include "cowl_ret.h"
#include "cowl_table.h"
#include "cowl_vector.h"
#include <stddef.h>

static inline cowl_ret add_prefix(CowlOntology *onto, CowlPrefixDecl *decl) {
    CowlPrefixMap *pm = cowl_ontology_get_prefix_map(onto);
    return cowl_prefix_map_add(pm, decl->prefix, decl->ns, true);
}

static inline cowl_ret remove_prefix(CowlOntology *onto, CowlPrefixDecl *decl) {
    CowlPrefixMap *pm = cowl_ontology_get_prefix_map(onto);
    cowl_ret ret_prefix = cowl_prefix_map_remove_prefix(pm, decl->prefix);
    cowl_ret ret_ns = cowl_prefix_map_remove_ns(pm, decl->ns);
    return cowl_is_err(ret_prefix) ? ret_prefix : ret_ns;
}

static inline cowl_ret add_to_ontology(CowlOntology *onto, cowl_part part, void *value) {
    switch (part) {
        case COWL_PART_PREFIX_DECL: return add_prefix(onto, value);
        case COWL_PART_IRI: return cowl_ontology_set_iri(onto, value);
        case COWL_PART_VERSION: return cowl_ontology_set_version(onto, value);
        case COWL_PART_IMPORT: return cowl_ontology_add_import(onto, value);
        case COWL_PART_ANNOTATION: return cowl_ontology_add_annot(onto, value);
        case COWL_PART_AXIOM: return cowl_ontology_add_axiom(onto, value);
        default: return COWL_OK;
    }
}

static inline cowl_ret remove_from_ontology(CowlOntology *onto, cowl_part part, void *value) {
    switch (part) {
        case COWL_PART_PREFIX_DECL: return remove_prefix(onto, value);
        case COWL_PART_IRI: return cowl_ontology_set_iri(onto, NULL);
        case COWL_PART_VERSION: return cowl_ontology_set_version(onto, NULL);
        case COWL_PART_IMPORT: return cowl_ontology_remove_import(onto, value);
        case COWL_PART_ANNOTATION: return cowl_ontology_remove_annot(onto, value);
        case COWL_PART_AXIOM: return cowl_ontology_remove_axiom(onto, value);
        default: return COWL_OK;
    }
}

static cowl_ret change_ontology(void *onto, CowlChange change) {
    if (change.type == COWL_CHANGE_ADD) {
        return add_to_ontology(onto, change.part, change.value);
    }
    return remove_from_ontology(onto, change.part, change.value);
}

CowlChangeHandler cowl_change_handler_to_ontology(CowlOntology *onto) {
    return (CowlChangeHandler){
        .ctx = onto,
        .handle = change_ontology,
    };
}

static bool handle_change(void *ctx, CowlAny *obj) {
    void **actx = (void **)ctx;
    cowl_ret *ret = actx[0];
    CowlChangeHandler *handler = actx[1];
    CowlChange *change = actx[2];
    change->value = obj;
    return cowl_is_ok(*ret = cowl_change_handler_handle(handler, *change));
}

cowl_ret cowl_change_handler_handle_ontology(CowlChangeHandler *handler, CowlOntology *onto,
                                             cowl_change_type type) {
    cowl_ret ret = COWL_OK;
    CowlChange change = { .type = type };

    change.part = COWL_PART_PREFIX_DECL;
    CowlPrefixMap *pm = cowl_ontology_get_prefix_map(onto);
    CowlTable *table = cowl_prefix_map_get_table(pm, false);

    cowl_table_foreach (table, e) {
        CowlPrefixDecl decl = { .prefix = *e.key, .ns = *e.val };
        change.value = &decl;
        if ((ret = cowl_change_handler_handle(handler, change))) return ret;
    }

    if ((change.value = cowl_ontology_get_iri(onto))) {
        change.part = COWL_PART_IRI;
        if ((ret = cowl_change_handler_handle(handler, change))) return ret;
    }

    if ((change.value = cowl_ontology_get_version(onto))) {
        change.part = COWL_PART_VERSION;
        if ((ret = cowl_change_handler_handle(handler, change))) return ret;
    }

    CowlVector *annotations = cowl_ontology_get_annot(onto);
    change.part = COWL_PART_ANNOTATION;

    cowl_vector_foreach (annotations, annot) {
        change.value = *annot.item;
        if ((ret = cowl_change_handler_handle(handler, change))) return ret;
    }

    void *ctx[] = { &ret, handler, &change };
    CowlIterator iter = { .ctx = (void *)ctx, .for_each = handle_change };

    change.part = COWL_PART_IMPORT;
    if (!cowl_ontology_iterate_imports(onto, &iter)) return ret;

    change.part = COWL_PART_AXIOM;
    if (!cowl_ontology_iterate_axioms(onto, &iter)) return ret;

    return ret;
}
