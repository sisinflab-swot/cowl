/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_tests.h"
#include "cowl_axiom.h"
#include "cowl_axiom_filter.h"
#include "cowl_class.h"
#include "cowl_decl_axiom.h"
#include "cowl_istream.h"
#include "cowl_manager.h"
#include "cowl_ontology.h"
#include "cowl_sub_cls_axiom.h"
#include "cowl_sym_table.h"
#include "cowl_table.h"
#include "cowl_test_utils.h"
#include "cowl_vector.h"

// Utils

#define ONTO_NS "http://onto.owl#"
#define COWL_ONTOLOGY_LOG COWL_TEST_ONTOLOGY ".log"
#define COWL_ONTOLOGY_OUT "test_onto_out.owl"

static void cowl_test_manager_write_error(void *ctx, CowlError const *error) {
    UOStream *stream = (UOStream *)ctx;
    cowl_write_error(stream, error);
    cowl_write_static(stream, "\n");
}

// Tests

bool cowl_test_manager_lifecycle(void) {
    CowlManager *manager = cowl_manager();
    utest_assert_not_null(manager);
    cowl_release(manager);
    return true;
}

static cowl_ret count_annot(void *ctx, cowl_unused CowlAnnotation *obj) {
    (*((ulib_uint *)ctx))++;
    return COWL_OK;
}

static cowl_ret count_import(void *ctx, cowl_unused CowlIRI *import) {
    (*((ulib_uint *)ctx))++;
    return COWL_OK;
}

static cowl_ret count_axiom(void *ctx, cowl_unused CowlAnyAxiom *obj) {
    (*((ulib_uint *)ctx))++;
    return COWL_OK;
}

bool cowl_test_manager_read_ontology(void) {
    CowlManager *manager = cowl_manager();
    utest_assert_not_null(manager);

    CowlImportLoader loader = { manager, cowl_test_load_import };
    cowl_manager_set_import_loader(manager, loader);

    ulib_uint count = 0;
    CowlIStreamHandlers handlers = { &count };
    handlers.axiom = count_axiom;
    handlers.import = count_import;
    handlers.annot = count_annot;

    CowlIStream *stream = cowl_manager_get_istream(manager, handlers);
    cowl_ret ret = cowl_istream_process_path(stream, ustring_literal(COWL_TEST_ONTOLOGY));
    utest_assert_uint(ret, ==, COWL_OK);

    UOStream ostream;
    utest_assert_critical(uostream_to_path(&ostream, COWL_ONTOLOGY_LOG) == USTREAM_OK);

    CowlErrorHandler handler = { &ostream, cowl_test_manager_write_error };
    cowl_manager_set_error_handler(manager, handler);

    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    utest_assert_not_null(onto);
    utest_assert_uint(cowl_manager_ontology_count(manager), ==, 2);

    ulib_uint true_count = cowl_vector_count(cowl_ontology_get_annot(onto));
    true_count += cowl_ontology_imports_count(onto, false) + cowl_ontology_axiom_count(onto, false);
    utest_assert_uint(count, ==, true_count);

    count = 0;
    ret = cowl_istream_process_ontology(stream, onto);
    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(count, ==, true_count);

    ret = cowl_manager_write_path(manager, onto, ustring_literal(COWL_ONTOLOGY_LOG));
    utest_assert_uint(ret, ==, COWL_OK);

    cowl_release(onto);
    utest_assert_uint(cowl_manager_ontology_count(manager), ==, 0);

    cowl_release_all(manager, stream);
    return true;
}

static bool cowl_test_manager_write_ontology_path(UString path) {
    CowlManager *manager = cowl_manager();
    utest_assert_not_null(manager);

    CowlOntology *onto_in = cowl_manager_read_path(manager, path);
    utest_assert_not_null(onto_in);

    CowlSymTable *st = cowl_ontology_get_sym_table(onto_in);
    cowl_sym_table_register_prefix_raw(st, ustring_literal("dc"),
                                       ustring_literal("http://purl.org/dc/elements/1.1/"), false);
    cowl_sym_table_register_prefix_raw(st, ustring_literal("dcterms"),
                                       ustring_literal("http://purl.org/dc/terms/"), false);

    cowl_ret ret = cowl_manager_write_path(manager, onto_in, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_uint(ret, ==, COWL_OK);

    CowlOntology *onto_out = cowl_manager_read_path(manager, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_not_null(onto_out);

    // Check that the written ontology is syntactically equal to the test ontology.
    cowl_assert_equal(ontology, onto_in, onto_out);

    UVec(CowlObjectPtr) imports_in = uvec(CowlObjectPtr);
    CowlIterator iter = cowl_iterator_vec(&imports_in, false);
    cowl_ontology_iterate_import_iris(onto_in, &iter, false);
    UVec(CowlObjectPtr) imports_out = uvec(CowlObjectPtr);
    iter = cowl_iterator_vec(&imports_out, false);
    cowl_ontology_iterate_import_iris(onto_out, &iter, false);
    utest_assert(uvec_equals(CowlObjectPtr, &imports_in, &imports_out));
    uvec_deinit(CowlObjectPtr, &imports_in);
    uvec_deinit(CowlObjectPtr, &imports_out);

    CowlVector *annot_in = cowl_ontology_get_annot(onto_in);
    CowlVector *annot_out = cowl_ontology_get_annot(onto_out);
    cowl_assert_equal(vector, annot_in, annot_out);

    UHash(CowlObjectTable) axioms_in = uhset(CowlObjectTable);
    iter = cowl_iterator_set(&axioms_in, false);
    cowl_ontology_iterate_axioms(onto_in, &iter, false);

    UHash(CowlObjectTable) axioms_out = uhset(CowlObjectTable);
    iter = cowl_iterator_set(&axioms_out, false);
    cowl_ontology_iterate_axioms(onto_out, &iter, false);

    utest_assert(uhset_equals(CowlObjectTable, &axioms_in, &axioms_out));

    uhash_deinit(CowlObjectTable, &axioms_in);
    uhash_deinit(CowlObjectTable, &axioms_out);
    cowl_release_all(onto_in, onto_out, manager);
    return true;
}

bool cowl_test_manager_write_ontology(void) {
    utest_assert(cowl_test_manager_write_ontology_path(ustring_literal(COWL_TEST_ONTOLOGY)));
    utest_assert(cowl_test_manager_write_ontology_path(ustring_literal(COWL_TEST_IMPORT)));
    return true;
}

static bool filter_axiom(void *cls, CowlAny *axiom) {
    return cowl_axiom_has_operand(axiom, cls, COWL_PS_ANY);
}

bool cowl_test_manager_edit_ontology(void) {
    CowlManager *manager = cowl_manager();
    CowlOntology *onto = cowl_manager_get_ontology(manager, NULL);
    utest_assert_not_null(onto);
    utest_assert_uint(cowl_manager_ontology_count(manager), ==, 1);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 0);

    CowlClass *a = cowl_class_from_static(ONTO_NS "A");
    CowlClass *b = cowl_class_from_static(ONTO_NS "B");

    CowlDeclAxiom *decl_axiom = cowl_decl_axiom(a, NULL);
    cowl_ret ret = cowl_ontology_add_axiom(onto, decl_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    cowl_release(decl_axiom);

    decl_axiom = cowl_decl_axiom(b, NULL);
    ret = cowl_ontology_add_axiom(onto, decl_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    cowl_release(decl_axiom);

    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 2);

    CowlSubClsAxiom *sub_axiom = cowl_sub_cls_axiom(a, b, NULL);
    cowl_release_all(a, b);

    ret = cowl_ontology_add_axiom(onto, sub_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 3);

    utest_assert(cowl_ontology_remove_axiom(onto, sub_axiom));
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 2);

    cowl_ontology_add_axiom(onto, sub_axiom);

    CowlAxiomFilter af = cowl_axiom_filter(COWL_AF_DECL | COWL_AF_SUB_CLASS);
    cowl_axiom_filter_add_primitive(&af, a);
    CowlFilter closure = { a, filter_axiom };
    cowl_axiom_filter_set_closure(&af, closure);

    utest_assert_uint(cowl_ontology_remove_axioms_matching(onto, &af), ==, 2);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 1);

    cowl_release_all(sub_axiom, onto, manager);
    return true;
}
