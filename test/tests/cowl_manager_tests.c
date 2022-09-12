/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_tests.h"
#include "cowl_class.h"
#include "cowl_decl_axiom.h"
#include "cowl_editor.h"
#include "cowl_manager.h"
#include "cowl_ontology.h"
#include "cowl_sub_cls_axiom.h"
#include "cowl_string.h"
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
    CowlManager *manager = cowl_manager_get();
    utest_assert_not_null(manager);
    cowl_manager_release(manager);
    return true;
}

bool cowl_test_manager_read_ontology(void) {
    CowlManager *manager = cowl_manager_get();
    utest_assert_not_null(manager);

    CowlImportLoader loader = cowl_import_loader(manager, cowl_test_load_import, NULL);
    cowl_manager_set_import_loader(manager, loader);

    UOStream stream;
    utest_assert_critical(uostream_to_path(&stream, COWL_ONTOLOGY_LOG) == USTREAM_OK);

    CowlErrorHandler handler = cowl_error_handler(&stream, cowl_test_manager_write_error, NULL);
    cowl_manager_set_error_handler(manager, handler);

    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    utest_assert_not_null(onto);

    cowl_ret ret = cowl_manager_write_path(manager, onto, ustring_literal(COWL_ONTOLOGY_LOG));
    utest_assert_uint(ret, ==, COWL_OK);

    cowl_ontology_release(onto);
    cowl_manager_release(manager);

    return true;
}

bool cowl_test_manager_write_ontology(void) {
    CowlManager *manager = cowl_manager_get();
    utest_assert_not_null(manager);

    CowlOntology *onto_in = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    utest_assert_not_null(onto_in);

    cowl_ret ret = cowl_manager_write_path(manager, onto_in, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_uint(ret, ==, COWL_OK);

    CowlOntology *onto_out = cowl_manager_read_path(manager, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_not_null(onto_out);

    // Check that the written ontology is syntactically equal to the test ontology.
    cowl_assert_equal(ontology, onto_in, onto_out);

    CowlVector *annot_in = cowl_ontology_get_annot(onto_in);
    CowlVector *annot_out = cowl_ontology_get_annot(onto_out);
    cowl_assert_equal(vector, annot_in, annot_out);

    UHash(CowlObjectTable) axioms_in = uhset(CowlObjectTable);
    CowlIterator iter = cowl_iterator_set(&axioms_in);
    cowl_ontology_iterate_axioms(onto_in, &iter, false);

    UHash(CowlObjectTable) axioms_out = uhset(CowlObjectTable);
    iter = cowl_iterator_set(&axioms_out);
    cowl_ontology_iterate_axioms(onto_out, &iter, false);

    utest_assert(uhset_equals(CowlObjectTable, &axioms_in, &axioms_out));

    uhash_deinit(CowlObjectTable, &axioms_in);
    uhash_deinit(CowlObjectTable, &axioms_out);
    cowl_ontology_release(onto_in);
    cowl_ontology_release(onto_out);
    cowl_manager_release(manager);

    return true;
}

bool cowl_test_manager_edit_ontology(void) {
    CowlManager *manager = cowl_manager_get();
    CowlOntology *onto = cowl_manager_get_ontology(manager, NULL);
    utest_assert_not_null(onto);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 0);

    CowlEditor *editor = cowl_manager_get_editor(manager, onto);
    utest_assert_not_null(editor);

    CowlClass *a = cowl_class_from_static(ONTO_NS "A");
    CowlClass *b = cowl_class_from_static(ONTO_NS "B");

    CowlDeclAxiom *decl_axiom = cowl_decl_axiom_get((CowlEntity *)a, NULL);
    cowl_ret ret = cowl_editor_add_axiom(editor, (CowlAxiom *)decl_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    cowl_decl_axiom_release(decl_axiom);

    decl_axiom = cowl_decl_axiom_get((CowlEntity *)b, NULL);
    ret = cowl_editor_add_axiom(editor, (CowlAxiom *)decl_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    cowl_decl_axiom_release(decl_axiom);

    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 2);

    CowlSubClsAxiom *sub_axiom = cowl_sub_cls_axiom_get((CowlClsExp *)a, (CowlClsExp *)b, NULL);
    cowl_class_release(a);
    cowl_class_release(b);

    ret = cowl_editor_add_axiom(editor, (CowlAxiom *)sub_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 3);

    ret = cowl_editor_remove_axiom(editor, (CowlAxiom *)sub_axiom);
    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_ontology_axiom_count(onto, false), ==, 2);

    cowl_sub_cls_axiom_release(sub_axiom);
    cowl_ontology_release(onto);
    cowl_manager_release(manager);
    return true;
}
