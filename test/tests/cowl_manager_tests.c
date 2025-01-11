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
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"
#include <stddef.h>
#include <stdio.h>

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
    CowlOntology *import = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_IMPORT));

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

    CowlManager *other_manager = cowl_manager();
    utest_assert_not_null(other_manager);

    ret = cowl_ontology_set_manager(onto, other_manager);
    utest_assert_uint(ret, ==, COWL_OK);
    utest_assert_uint(cowl_manager_ontology_count(manager), ==, 1);
    utest_assert_uint(cowl_manager_ontology_count(other_manager), ==, 1);

    cowl_release(onto);
    utest_assert_uint(cowl_manager_ontology_count(other_manager), ==, 0);

    cowl_release(import);
    utest_assert_uint(cowl_manager_ontology_count(manager), ==, 0);

    cowl_release_all(manager, other_manager, stream);
    return true;
}

static bool equal_ontologies(CowlOntology *a, CowlOntology *b) {
    if (cowl_ontology_get_iri(a) != cowl_ontology_get_iri(b)) return false;
    if (cowl_ontology_get_version(a) != cowl_ontology_get_version(b)) return false;

    UVec(CowlObjectPtr) imports_a = uvec(CowlObjectPtr);
    CowlIterator iter = cowl_iterator_vec(&imports_a, false);
    cowl_ontology_iterate_import_iris(a, &iter, false);

    UVec(CowlObjectPtr) imports_b = uvec(CowlObjectPtr);
    iter = cowl_iterator_vec(&imports_b, false);
    cowl_ontology_iterate_import_iris(b, &iter, false);

    bool equal = uvec_equals(CowlObjectPtr, &imports_a, &imports_b);

    uvec_deinit(CowlObjectPtr, &imports_a);
    uvec_deinit(CowlObjectPtr, &imports_b);

    if (!equal) return false;

    CowlVector *annot_a = cowl_ontology_get_annot(a);
    CowlVector *annot_b = cowl_ontology_get_annot(b);
    if (!cowl_equals(annot_a, annot_b)) return false;

    UHash(CowlObjectTable) axioms_a = uhset(CowlObjectTable);
    iter = cowl_iterator_set(&axioms_a, false);
    cowl_ontology_iterate_axioms(a, &iter, false);

    UHash(CowlObjectTable) axioms_b = uhset(CowlObjectTable);
    iter = cowl_iterator_set(&axioms_b, false);
    cowl_ontology_iterate_axioms(b, &iter, false);

    equal = uhset_equals(CowlObjectTable, &axioms_a, &axioms_b);

    uhash_deinit(CowlObjectTable, &axioms_a);
    uhash_deinit(CowlObjectTable, &axioms_b);

    return equal;
}

static bool test_format(UString path, CowlReader reader, CowlWriter writer) {
    CowlManager *manager = cowl_manager();
    utest_assert_not_null(manager);

    CowlOntology *onto_in = cowl_manager_read_path(manager, path);
    utest_assert_not_null(onto_in);

    cowl_manager_set_reader(manager, reader);
    cowl_manager_set_writer(manager, writer);

    cowl_ret ret = cowl_manager_write_path(manager, onto_in, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_uint(ret, ==, COWL_OK);

    CowlOntology *onto_out = cowl_manager_read_path(manager, ustring_literal(COWL_ONTOLOGY_OUT));
    utest_assert_not_null(onto_out);

    bool equal = equal_ontologies(onto_in, onto_out);

    if (!equal) {
        cowl_manager_set_writer(manager, cowl_writer_functional());
        cowl_manager_write_path(manager, onto_in, ustring_literal(COWL_ONTOLOGY_LOG));
    }

    utest_assert(equal);
    cowl_release_all(onto_in, onto_out, manager);
    return true;
}

bool cowl_test_manager_write_ontology(void) {
    UString const onto_path = ustring_literal(COWL_TEST_ONTOLOGY);
    UString const import_path = ustring_literal(COWL_TEST_IMPORT);

    struct {
        CowlReader reader;
        CowlWriter writer;
    } const formats[] = {
#if COWL_READER_FUNCTIONAL && COWL_WRITER_FUNCTIONAL
        { cowl_reader_functional(), cowl_writer_functional() },
#endif
    };

    for (ulib_uint i = 0; i < ulib_array_count(formats); ++i) {
        printf("Testing %s format.\n", formats[i].reader.name);
        utest_assert(test_format(onto_path, formats[i].reader, formats[i].writer));
        utest_assert(test_format(import_path, formats[i].reader, formats[i].writer));
    }

    return true;
}

static bool filter_axiom(void *cls, CowlAny *axiom) {
    return cowl_axiom_has_operand(axiom, cls, COWL_PS_ANY);
}

bool cowl_test_manager_edit_ontology(void) {
    CowlManager *manager = cowl_manager();
    CowlOntology *onto = cowl_manager_new_ontology(manager);
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
