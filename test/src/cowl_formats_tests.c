/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_formats_tests.h"
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"
#include <stddef.h>
#include <stdio.h>

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
    cowl_ontology_iterate_imports(a, &iter);

    iter = cowl_iterator_set(&b_set, false);
    cowl_ontology_iterate_imports(b, &iter);

    uhset_diff(CowlObjectTable, &a_set, &b_set, NULL);
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
    cowl_ontology_iterate_axioms(a, &iter);

    iter = cowl_iterator_set(&b_set, false);
    cowl_ontology_iterate_axioms(b, &iter);

    uhset_diff(CowlObjectTable, &a_set, &b_set, NULL);
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
    UString out_path = ustring_with_format("%s_%s.log", reader, path);
    cowl_ontology_to_path(out, out_path);
    ustring_deinit(&out_path);

    out_path = ustring_with_format("%s_%s_in_out_diff.log", reader, path);
    cowl_ontology_to_path(in_minus_out, out_path);
    ustring_deinit(&out_path);

    out_path = ustring_with_format("%s_%s_out_in_diff.log", reader, path);
    cowl_ontology_to_path(out_minus_in, out_path);
    ustring_deinit(&out_path);
}

static void test_format(UString path, CowlReader *reader, CowlWriter *writer) {
    CowlOntology *onto_in = cowl_ontology_at_path(path);
    utest_assert_not_null(onto_in);

    UString out_path = ustring_literal("test_onto_out.owl");
    cowl_assert_ok(cowl_writer_write_ontology_to_path(writer, out_path, onto_in));
    CowlOntology *onto_out = cowl_reader_read_ontology_at_path(reader, out_path);
    utest_assert_not_null(onto_out);

    CowlOntology *in_minus_out = cowl_ontology();
    CowlOntology *out_minus_in = cowl_ontology();

    if (ontologies_differ(onto_in, onto_out, in_minus_out, out_minus_in)) {
        char const *name = cowl_reader_get_name(reader);
        char const *path_str = ustring_data(path);
        log_diff(name, path_str, onto_out, in_minus_out, out_minus_in);
        utest_log_failure_reason("Round-trip test failed for \"%s\" format.", name, path_str);
        utest_fail();
    }

    cowl_release_all(onto_in, onto_out, in_minus_out, out_minus_in);
}

void cowl_test_formats(void) {
    UString const onto_path = ustring_literal(COWL_TEST_ONTOLOGY);
    UString const import_path = ustring_literal(COWL_TEST_IMPORT);

    struct {
        CowlReader *(*reader)(void);
        CowlWriter *(*writer)(void);
    } const formats[] = {
#if COWL_READER_FUNCTIONAL && COWL_WRITER_FUNCTIONAL
        { cowl_reader_functional, cowl_writer_functional },
#endif
    };

    for (ulib_uint i = 0; i < ulib_array_count(formats); ++i) {
        CowlReader *reader = formats[i].reader();
        CowlWriter *writer = formats[i].writer();
        ulog_info("\"%s\" format test started", cowl_writer_get_name(writer));
        utest_sub(test_format(onto_path, reader, writer));
        utest_sub(test_format(import_path, reader, writer));
        cowl_release_all(reader, writer);
    }
}
