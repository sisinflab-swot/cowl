/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_ontology_tests.h"
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"
#include <stddef.h>

#define test_onto_iri "http://visualdataweb.de/ontobench/ontology/1/"
#define test_class "Class1"
#define test_datatype "DataUnionOf_Datatype1"
#define test_obj_prop "equivalentObjectProperty_1"
#define test_data_prop "equivalentDataProperty_1"
#define test_annot_prop "customAnnotationProperty"
#define test_named_ind "AllDifferent_Individual1"
#define test_iri "ClassWithInfos"

static CowlOntology *onto = NULL;

static ulib_uint const test_onto_import_count = 2;
static ulib_uint const test_onto_axiom_count = 584;

static ulib_uint const test_primitive_count[] = { 105, 43, 48, 72, 25, 18, 1, 12 };
static ulib_uint const test_primitive_axiom_count[] = { 16, 2, 4, 4, 2, 2, 1, 8 };

static ulib_uint axiom_counts_by_type[COWL_AT_COUNT] = { 0 };

static void axiom_counts_by_type_init(void) {
    axiom_counts_by_type[COWL_AT_DECL] = 264;
    axiom_counts_by_type[COWL_AT_DATATYPE_DEF] = 2;
    axiom_counts_by_type[COWL_AT_SUB_CLASS] = 35;
    axiom_counts_by_type[COWL_AT_EQUIV_CLASSES] = 4;
    axiom_counts_by_type[COWL_AT_DISJ_CLASSES] = 4;
    axiom_counts_by_type[COWL_AT_DISJ_UNION] = 1;
    axiom_counts_by_type[COWL_AT_CLASS_ASSERT] = 2;
    axiom_counts_by_type[COWL_AT_SAME_IND] = 1;
    axiom_counts_by_type[COWL_AT_DIFF_IND] = 1;
    axiom_counts_by_type[COWL_AT_OBJ_PROP_ASSERT] = 1;
    axiom_counts_by_type[COWL_AT_NEG_OBJ_PROP_ASSERT] = 1;
    axiom_counts_by_type[COWL_AT_DATA_PROP_ASSERT] = 13;
    axiom_counts_by_type[COWL_AT_NEG_DATA_PROP_ASSERT] = 1;
    axiom_counts_by_type[COWL_AT_SUB_OBJ_PROP] = 2;
    axiom_counts_by_type[COWL_AT_INV_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_EQUIV_OBJ_PROP] = 2;
    axiom_counts_by_type[COWL_AT_DISJ_OBJ_PROP] = 2;
    axiom_counts_by_type[COWL_AT_FUNC_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_INV_FUNC_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_SYMM_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_ASYMM_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_TRANS_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_REFL_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_IRREFL_OBJ_PROP] = 1;
    axiom_counts_by_type[COWL_AT_OBJ_PROP_DOMAIN] = 39;
    axiom_counts_by_type[COWL_AT_OBJ_PROP_RANGE] = 39;
    axiom_counts_by_type[COWL_AT_SUB_DATA_PROP] = 1;
    axiom_counts_by_type[COWL_AT_EQUIV_DATA_PROP] = 1;
    axiom_counts_by_type[COWL_AT_DISJ_DATA_PROP] = 2;
    axiom_counts_by_type[COWL_AT_FUNC_DATA_PROP] = 1;
    axiom_counts_by_type[COWL_AT_DATA_PROP_DOMAIN] = 66;
    axiom_counts_by_type[COWL_AT_DATA_PROP_RANGE] = 66;
    axiom_counts_by_type[COWL_AT_HAS_KEY] = 3;
    axiom_counts_by_type[COWL_AT_ANNOT_ASSERT] = 19;
    axiom_counts_by_type[COWL_AT_SUB_ANNOT_PROP] = 1;
    axiom_counts_by_type[COWL_AT_ANNOT_PROP_DOMAIN] = 1;
    axiom_counts_by_type[COWL_AT_ANNOT_PROP_RANGE] = 1;
}

static void log_error(CowlReader *reader) {
    UString str = cowl_error_to_string(cowl_reader_last_error(reader));
    ulog_error("%s", ustring_data(str));
    ustring_deinit(&str);
}

void cowl_test_ontology_init(void) {
    axiom_counts_by_type_init();

    CowlReader *reader = cowl_get_reader();
    onto = cowl_reader_read_ontology_from_path(reader, ustring_literal(COWL_TEST_IMPORT), NULL);
    if (!onto) log_error(reader);
    utest_assert_fatal(onto);

    CowlChangeHandler handler = cowl_change_handler_to_ontology(onto);
    cowl_ret ret = cowl_reader_read_path(reader, ustring_literal(COWL_TEST_ONTOLOGY), handler);
    if (cowl_is_err(ret)) log_error(reader);
    utest_assert_fatal(cowl_is_ok(ret));
}

void cowl_test_ontology_deinit(void) {
    cowl_release(onto);
}

void cowl_test_ontology_get_iri_version(void) {
    CowlIRI *expected_onto_iri = cowl_iri_from_literal(test_onto_iri);
    cowl_assert_equal(iri, cowl_ontology_get_iri(onto), expected_onto_iri);
    utest_assert_ptr(cowl_ontology_get_version(onto), ==, NULL);
    cowl_release(expected_onto_iri);
}

void cowl_test_ontology_axiom_count(void) {
    ulib_uint axiom_count = cowl_ontology_axiom_count(onto);
    utest_assert_uint(axiom_count, ==, test_onto_axiom_count);
}

void cowl_test_ontology_imports_count(void) {
    ulib_uint imports_count = cowl_ontology_import_count(onto);
    utest_assert_uint(imports_count, ==, test_onto_import_count);
}

void cowl_test_ontology_axiom_count_for_type(void) {
    for (ulib_uint type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        ulib_uint expected_count = axiom_counts_by_type[type];
        ulib_uint count = cowl_ontology_axiom_count_for_type(onto, (CowlAxiomType)type);
        utest_assert_uint(count, ==, expected_count);
    }
}

void cowl_test_ontology_axiom_count_for_types(void) {
    ulib_uint expected = axiom_counts_by_type[COWL_AT_SUB_CLASS] +
                         axiom_counts_by_type[COWL_AT_OBJ_PROP_ASSERT] +
                         axiom_counts_by_type[COWL_AT_ANNOT_ASSERT];
    CowlAxiomFlags types = COWL_AF_SUB_CLASS | COWL_AF_OBJ_PROP_ASSERT | COWL_AF_ANNOT_ASSERT;
    ulib_uint count = cowl_ontology_axiom_count_for_types(onto, types);
    utest_assert_uint(count, ==, expected);

    expected = test_onto_axiom_count;
    count = cowl_ontology_axiom_count_for_types(onto, COWL_AF_ALL);
    utest_assert_uint(count, ==, expected);
}

void cowl_test_ontology_primitive_count(void) {
    for (ulib_uint i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        CowlPrimitiveFlags flags = cowl_primitive_flags_from_type((CowlPrimitiveType)i);
        ulib_uint c = cowl_ontology_primitive_count(onto, flags);
        utest_assert_uint(c, ==, test_primitive_count[i]);
    }
}

static cowl_ret cowl_test_get_first_anon_ind(void *ctx, CowlAny *obj) {
    *((CowlAny **)ctx) = obj;
    return COWL_STOP;
}

void cowl_test_ontology_axiom_count_for_primitive(void) {
    CowlAnyPrimitive *primitive = cowl_class_from_literal(test_onto_iri test_class);
    ulib_uint count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_CLASS]);

    primitive = cowl_datatype_from_literal(test_onto_iri test_datatype);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATATYPE]);

    primitive = cowl_obj_prop_from_literal(test_onto_iri test_obj_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_OBJ_PROP]);

    primitive = cowl_data_prop_from_literal(test_onto_iri test_data_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATA_PROP]);

    primitive = cowl_annot_prop_from_literal(test_onto_iri test_annot_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_ANNOT_PROP]);

    primitive = cowl_named_ind_from_literal(test_onto_iri test_named_ind);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_NAMED_IND]);

    primitive = cowl_iri_from_literal(test_onto_iri test_iri);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_IRI]);

    CowlIterator iter = { (void *)&primitive, cowl_test_get_first_anon_ind };
    cowl_ontology_iterate_primitives(onto, COWL_PF_ANON_IND, &iter);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_ANON_IND]);
}

#define cowl_test_has_primitive(TYPE)                                                              \
    do {                                                                                           \
        CowlAnyPrimitive *p = cowl_##TYPE##_from_literal(test_onto_iri test_##TYPE);               \
        utest_assert(cowl_ontology_has_primitive(onto, p));                                        \
        cowl_release(p);                                                                           \
        p = cowl_##TYPE##_from_literal(test_onto_iri test_##TYPE "_not_present");                  \
        utest_assert_false(cowl_ontology_has_primitive(onto, p));                                  \
        cowl_release(p);                                                                           \
    } while (0)

void cowl_test_ontology_has_primitive(void) {
    cowl_test_has_primitive(class);
    cowl_test_has_primitive(datatype);
    cowl_test_has_primitive(named_ind);
    cowl_test_has_primitive(obj_prop);
    cowl_test_has_primitive(data_prop);
    cowl_test_has_primitive(annot_prop);
    cowl_test_has_primitive(iri);
}

static CowlDatatypeDefAxiom *generate_datatype_def(char const *v1, char const *v2, char const *v3) {
    CowlDatatype *dt = cowl_datatype_from_literal(test_onto_iri "DataOneOf");
    CowlLiteral *l1 = cowl_literal_plain(ustring_wrap_cstring(v1));
    CowlLiteral *l2 = cowl_literal_plain(ustring_wrap_cstring(v2));
    CowlLiteral *l3 = cowl_literal_plain(ustring_wrap_cstring(v3));
    CowlVector *values = cowl_vector_of(l1, l2, l3);
    CowlDataOneOf *one_of = cowl_data_one_of(values);
    CowlDatatypeDefAxiom *axiom = cowl_datatype_def_axiom(dt, one_of, NULL);
    cowl_release_all(dt, l1, l2, l3, values, one_of);
    return axiom;
}

void cowl_test_ontology_has_axiom(void) {
    CowlDatatypeDefAxiom *axiom = NULL;
    // DatatypeDefinition(:DataOneOf DataOneOf("DataOneOf_Literal1"^^xsd:string
    // "DataOneOf_Literal2"^^xsd:string "DataOneOf_Literal3"^^xsd:string))
    axiom = generate_datatype_def("DataOneOf_Literal3", "DataOneOf_Literal2", "DataOneOf_Literal1");
    utest_assert(cowl_ontology_has_axiom(onto, axiom));
    cowl_release(axiom);

    // DatatypeDefinition(:DataOneOf DataOneOf("DataOneOf_Literal1"^^xsd:string
    // "DataOneOf_Literal2"^^xsd:string "DataOneOf_Literal4"^^xsd:string))
    axiom = generate_datatype_def("DataOneOf_Literal4", "DataOneOf_Literal2", "DataOneOf_Literal1");
    utest_assert_false(cowl_ontology_has_axiom(onto, axiom));
    cowl_release(axiom);
}

static bool filter_axiom(void *cls, CowlAny *axiom) {
    return cowl_axiom_has_operand(axiom, cls, COWL_PS_ANY);
}

void cowl_test_ontology_edit(void) {
    CowlOntology *onto = cowl_ontology();
    utest_assert_not_null(onto);
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 0);

    CowlClass *a = cowl_class_from_literal(test_onto_iri "A");
    CowlClass *b = cowl_class_from_literal(test_onto_iri "B");

    CowlDeclAxiom *decl_axiom = cowl_decl_axiom(a, NULL);
    cowl_assert_ok(cowl_ontology_add_axiom(onto, decl_axiom));
    utest_assert(cowl_ontology_has_axiom(onto, decl_axiom));
    cowl_release(decl_axiom);
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 1);

    decl_axiom = cowl_decl_axiom(b, NULL);
    cowl_assert_ok(cowl_ontology_add_axiom(onto, decl_axiom));
    utest_assert(cowl_ontology_has_axiom(onto, decl_axiom));
    cowl_release(decl_axiom);
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 2);

    CowlSubClsAxiom *sub_axiom = cowl_sub_cls_axiom(a, b, NULL);
    cowl_release_all(a, b);

    cowl_assert_ok(cowl_ontology_add_axiom(onto, sub_axiom));
    utest_assert(cowl_ontology_has_axiom(onto, sub_axiom));
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 3);

    utest_assert(cowl_ontology_remove_axiom(onto, sub_axiom));
    utest_assert_false(cowl_ontology_has_axiom(onto, sub_axiom));
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 2);

    cowl_ontology_add_axiom(onto, sub_axiom);

    CowlAxiomFilter af = cowl_axiom_filter(COWL_AF_DECL | COWL_AF_SUB_CLASS);
    cowl_axiom_filter_add_primitive(&af, a);
    CowlFilter closure = { a, filter_axiom };
    cowl_axiom_filter_set_closure(&af, closure);

    utest_assert_uint(cowl_ontology_remove_axioms_matching(onto, &af), ==, 2);
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 1);

    cowl_release_all(sub_axiom, onto);
}

static cowl_ret count_primitives_foreach(void *ctx, CowlAny *obj) {
    // Dereference so that dangling index keys are caught by the sanitizers.
    if (cowl_is_primitive(obj)) ++(*(ulib_uint *)ctx);
    return COWL_CONTINUE;
}

void cowl_test_ontology_add_remove(void) {
    CowlOntology *onto = cowl_ontology();
    CowlClass *cls = cowl_class_from_literal(test_onto_iri "A");
    CowlNamedInd *ind = cowl_named_ind_from_literal(test_onto_iri "a");
    CowlAnnotProp *prop = cowl_annot_prop_from_literal(test_onto_iri "p");
    CowlIRI *value = cowl_iri_from_literal(test_onto_iri "v");

    CowlAnnotation *annot = cowl_annotation(prop, value, NULL);
    CowlDeclAxiom *ind_decl = cowl_decl_axiom(ind, NULL);
    CowlDeclAxiom *prop_decl = cowl_decl_axiom(prop, NULL);
    CowlAnyAxiom *axioms[] = {
        ind_decl,
        prop_decl,
        cowl_sub_cls_axiom(cls, cls, NULL),
        cowl_cls_assert_axiom(cls, ind, NULL),
    };

    cowl_assert_ok(cowl_ontology_add_annot(onto, annot));
    for (ulib_uint i = 0; i < ulib_array_count(axioms); ++i) {
        cowl_assert_ok(cowl_ontology_add_axiom(onto, axioms[i]));
    }
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 4);
    utest_assert_uint(cowl_ontology_primitive_count(onto, COWL_PF_ALL), ==, 4);

    CowlAnyAxiom *axiom = cowl_decl_axiom(prop, NULL);
    utest_assert(cowl_ontology_remove_axiom(onto, axiom));
    cowl_release(axiom);
    utest_assert(cowl_ontology_has_primitive(onto, prop));
    utest_assert_uint(cowl_ontology_axiom_count_for_primitive(onto, prop), ==, 0);

    cowl_assert_ok(cowl_ontology_add_axiom(onto, prop_decl));
    utest_assert_uint(cowl_ontology_axiom_count_for_primitive(onto, prop), ==, 1);

    CowlAnnotation *equal_annot = cowl_annotation(prop, value, NULL);
    utest_assert(cowl_ontology_remove_annot(onto, equal_annot));
    cowl_release(equal_annot);
    utest_assert(cowl_ontology_has_primitive(onto, prop));
    utest_assert_false(cowl_ontology_has_primitive(onto, value));

    CowlAxiomFilter af = cowl_axiom_filter(COWL_AF_ALL);
    cowl_assert_ok(cowl_axiom_filter_add_primitive(&af, cls));
    utest_assert_uint(cowl_ontology_remove_axioms_matching(onto, &af), ==, 2);
    utest_assert_false(cowl_ontology_has_primitive(onto, cls));
    utest_assert(cowl_ontology_has_primitive(onto, ind));

    utest_assert(cowl_ontology_remove_axiom(onto, ind_decl));
    utest_assert(cowl_ontology_remove_axiom(onto, prop_decl));
    utest_assert_uint(cowl_ontology_axiom_count(onto), ==, 0);
    utest_assert_uint(cowl_ontology_primitive_count(onto, COWL_PF_ALL), ==, 0);

    for (ulib_uint i = 0; i < ulib_array_count(axioms); ++i) {
        cowl_release(axioms[i]);
    }
    cowl_release_all(annot, cls, ind, prop, value);

    ulib_uint count = 0;
    CowlIterator iter = { &count, count_primitives_foreach };
    cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter);
    utest_assert_uint(count, ==, 0);
    cowl_release(onto);
}
