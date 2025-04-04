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
    UString const log_path = ustring_literal("test_manager_read_ontology.log");

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
    utest_assert_critical(uostream_to_path(&ostream, ustring_data(log_path)) == USTREAM_OK);

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

    ret = cowl_manager_write_path(manager, onto, log_path);
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

static inline bool diff_iri_version(CowlOntology *a, CowlOntology *b, CowlOntology *diff) {
    bool different = false;
    if (cowl_ontology_get_iri(a) != cowl_ontology_get_iri(b)) {
        cowl_ontology_set_iri(diff, cowl_ontology_get_iri(a));
        different = true;
    }
    if (cowl_ontology_get_version(a) != cowl_ontology_get_version(b)) {
        cowl_ontology_set_version(diff, cowl_ontology_get_version(a));
        different = true;
    }
    return different;
}

static inline bool diff_annotations(CowlOntology *a, CowlOntology *b, CowlOntology *diff) {
    bool different = false;
    cowl_vector_foreach (cowl_ontology_get_annot(a), annot) {
        if (!cowl_vector_contains(cowl_ontology_get_annot(b), *annot.item)) {
            cowl_ontology_add_annot(diff, (CowlAnnotation *)*annot.item);
            different = true;
        }
    }
    return different;
}

static inline bool diff_imports(CowlOntology *a, CowlOntology *b, CowlOntology *diff) {
    bool different = false;

    UHash(CowlObjectTable) a_set = uhset(CowlObjectTable);
    UHash(CowlObjectTable) b_set = uhset(CowlObjectTable);

    CowlIterator iter = cowl_iterator_set(&a_set, false);
    cowl_ontology_iterate_import_iris(a, &iter, false);

    iter = cowl_iterator_set(&b_set, false);
    cowl_ontology_iterate_import_iris(b, &iter, false);

    uhset_diff(CowlObjectTable, &a_set, &b_set);
    uhash_foreach (CowlObjectTable, &a_set, i) {
        cowl_ontology_add_import(diff, (CowlIRI *)*i.key);
        different = true;
    }

    uhash_deinit(CowlObjectTable, &a_set);
    uhash_deinit(CowlObjectTable, &b_set);

    return different;
}

static inline bool diff_axioms(CowlOntology *a, CowlOntology *b, CowlOntology *diff) {
    bool different = false;

    UHash(CowlObjectTable) a_set = uhset(CowlObjectTable);
    UHash(CowlObjectTable) b_set = uhset(CowlObjectTable);

    CowlIterator iter = cowl_iterator_set(&a_set, false);
    cowl_ontology_iterate_axioms(a, &iter, false);

    iter = cowl_iterator_set(&b_set, false);
    cowl_ontology_iterate_axioms(b, &iter, false);

    uhset_diff(CowlObjectTable, &a_set, &b_set);
    uhash_foreach (CowlObjectTable, &a_set, i) {
        cowl_ontology_add_axiom(diff, *i.key);
        different = true;
    }

    uhash_deinit(CowlObjectTable, &a_set);
    uhash_deinit(CowlObjectTable, &b_set);

    return different;
}

static bool diff_ontologies(CowlOntology *a, CowlOntology *b, CowlOntology *diff) {
    bool different = false;
    different |= diff_iri_version(a, b, diff);
    different |= diff_annotations(a, b, diff);
    different |= diff_imports(a, b, diff);
    different |= diff_axioms(a, b, diff);
    return different;
}

static bool ontologies_differ(CowlOntology *a, CowlOntology *b, CowlOntology *a_minus_b,
                              CowlOntology *b_minus_a) {
    bool different = false;
    different |= diff_ontologies(a, b, a_minus_b);
    different |= diff_ontologies(b, a, b_minus_a);
    return different;
}

static void log_diff(char const *reader, char const *path, CowlOntology *out,
                     CowlOntology *in_minus_out, CowlOntology *out_minus_in) {
    CowlManager *manager = cowl_ontology_get_manager(out);
    cowl_manager_set_writer(manager, cowl_writer_default());

    UString out_path = ustring_with_format("%s_%s.log", reader, path);
    cowl_manager_write_path(manager, out, out_path);
    ustring_deinit(&out_path);

    out_path = ustring_with_format("%s_%s_in_out_diff.log", reader, path);
    cowl_manager_write_path(manager, in_minus_out, out_path);
    ustring_deinit(&out_path);

    out_path = ustring_with_format("%s_%s_out_in_diff.log", reader, path);
    cowl_manager_write_path(manager, out_minus_in, out_path);
    ustring_deinit(&out_path);
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

    CowlOntology *in_minus_out = cowl_manager_new_ontology(manager);
    CowlOntology *out_minus_in = cowl_manager_new_ontology(manager);

    bool differ = ontologies_differ(onto_in, onto_out, in_minus_out, out_minus_in);
    if (differ) log_diff(reader.name, ustring_data(path), onto_out, in_minus_out, out_minus_in);

    utest_assert_false(differ);
    cowl_release_all(onto_in, onto_out, in_minus_out, out_minus_in, manager);
    return true;
}

bool cowl_test_manager_write_ontology(void) {
    UString const onto_path = ustring_literal(COWL_TEST_ONTOLOGY);
    UString const import_path = ustring_literal(COWL_TEST_IMPORT);

    struct {
        CowlReader (*reader)(void);
        CowlWriter (*writer)(void);
    } const formats[] = {
#if COWL_READER_FUNCTIONAL && COWL_WRITER_FUNCTIONAL
        { cowl_reader_functional, cowl_writer_functional },
#endif
    };

    for (ulib_uint i = 0; i < ulib_array_count(formats); ++i) {
        CowlReader reader = formats[i].reader();
        printf("Testing %s format.\n", reader.name);
        utest_assert(test_format(onto_path, reader, formats[i].writer()));
        utest_assert(test_format(import_path, formats[i].reader(), formats[i].writer()));
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
