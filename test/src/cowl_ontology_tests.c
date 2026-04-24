/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
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

static ulib_uint const test_onto_imports_count = 1;
static ulib_uint const test_onto_axiom_count = 573;

static ulib_uint const test_primitives_count[] = { 105, 43, 48, 72, 25, 18, 1, 12 };
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
    axiom_counts_by_type[COWL_AT_DATA_PROP_ASSERT] = 2;
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

void cowl_test_ontology_init(void) {
    axiom_counts_by_type_init();

    onto = cowl_ontology_at_path(ustring_literal(COWL_TEST_IMPORT), NULL);
    utest_assert_fatal(onto);

    CowlReader *reader = cowl_get_reader();
    CowlChangeHandler handler = cowl_change_handler_to_ontology(onto);
    UString path = ustring_literal(COWL_TEST_ONTOLOGY);
    utest_assert_fatal(cowl_is_ok(cowl_reader_read_path(reader, path, handler)));
}

void cowl_test_ontology_deinit(void) {
    cowl_release(onto);
}

void cowl_test_ontology_get_iri_version(void) {
    CowlIRI *expected_onto_iri = cowl_iri_from_static(test_onto_iri);
    cowl_assert_equal(iri, cowl_ontology_get_iri(onto), expected_onto_iri);
    utest_assert_ptr(cowl_ontology_get_version(onto), ==, NULL);
    cowl_release(expected_onto_iri);
}

void cowl_test_ontology_axiom_count(void) {
    ulib_uint axiom_count = cowl_ontology_axiom_count(onto);
    utest_assert_uint(axiom_count, ==, test_onto_axiom_count);
}

void cowl_test_ontology_imports_count(void) {
    ulib_uint imports_count = cowl_ontology_imports_count(onto);
    utest_assert_uint(imports_count, ==, test_onto_imports_count);
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

void cowl_test_ontology_primitives_count(void) {
    for (ulib_uint i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        CowlPrimitiveFlags flags = cowl_primitive_flags_from_type((CowlPrimitiveType)i);
        ulib_uint c = cowl_ontology_primitives_count(onto, flags);
        utest_assert_uint(c, ==, test_primitives_count[i]);
    }
}

static cowl_ret cowl_test_get_first_anon_ind(void *ctx, CowlAny *obj) {
    *((CowlAny **)ctx) = obj;
    return COWL_STOP;
}

void cowl_test_ontology_axiom_count_for_primitive(void) {
    CowlAnyPrimitive *primitive = cowl_class_from_static(test_onto_iri test_class);
    ulib_uint count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_CLASS]);

    primitive = cowl_datatype_from_static(test_onto_iri test_datatype);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATATYPE]);

    primitive = cowl_obj_prop_from_static(test_onto_iri test_obj_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_OBJ_PROP]);

    primitive = cowl_data_prop_from_static(test_onto_iri test_data_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATA_PROP]);

    primitive = cowl_annot_prop_from_static(test_onto_iri test_annot_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_ANNOT_PROP]);

    primitive = cowl_named_ind_from_static(test_onto_iri test_named_ind);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_NAMED_IND]);

    primitive = cowl_iri_from_static(test_onto_iri test_iri);
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
        CowlAnyPrimitive *p = cowl_##TYPE##_from_static(test_onto_iri test_##TYPE);                \
        utest_assert(cowl_ontology_has_primitive(onto, p));                                        \
        cowl_release(p);                                                                           \
        p = cowl_##TYPE##_from_static(test_onto_iri test_##TYPE "_not_present");                   \
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
    CowlDatatype *dt = cowl_datatype_from_static(test_onto_iri "DataOneOf");
    CowlLiteral *l1 = cowl_literal_plain(ustring_wrap_cstring(v1));
    CowlLiteral *l2 = cowl_literal_plain(ustring_wrap_cstring(v2));
    CowlLiteral *l3 = cowl_literal_plain(ustring_wrap_cstring(v3));
    UVec(CowlObjectPtr) vec = uvec(CowlObjectPtr);
    uvec_push(CowlObjectPtr, &vec, l1);
    uvec_push(CowlObjectPtr, &vec, l2);
    uvec_push(CowlObjectPtr, &vec, l3);
    CowlVector *values = cowl_vector(&vec);
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

    CowlClass *a = cowl_class_from_static(test_onto_iri "A");
    CowlClass *b = cowl_class_from_static(test_onto_iri "B");

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
