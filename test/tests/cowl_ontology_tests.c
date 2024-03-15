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
#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_one_of.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_datatype_def_axiom.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_manager.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"
#include "cowl_ontology.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"
#include "cowl_vector.h"

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
static ulib_uint const test_onto_axiom_count = 571;

static ulib_uint const test_primitives_count[] = { 105, 48, 72, 27, 18, 1, 46, 12 };
static ulib_uint const test_primitive_axiom_count[] = { 16, 4, 4, 2, 2, 1, 2, 8 };

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
    axiom_counts_by_type[COWL_AT_HAS_KEY] = 1;
    axiom_counts_by_type[COWL_AT_ANNOT_ASSERT] = 19;
    axiom_counts_by_type[COWL_AT_SUB_ANNOT_PROP] = 1;
    axiom_counts_by_type[COWL_AT_ANNOT_PROP_DOMAIN] = 1;
    axiom_counts_by_type[COWL_AT_ANNOT_PROP_RANGE] = 1;
}

bool cowl_test_ontology_init(void) {
    axiom_counts_by_type_init();
    CowlManager *manager = cowl_manager();
    CowlImportLoader loader = { manager, cowl_test_load_import };
    cowl_manager_set_import_loader(manager, loader);
    onto = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    cowl_release(manager);
    utest_assert_critical(onto);
    return true;
}

bool cowl_test_ontology_deinit(void) {
    cowl_release(onto);
    return true;
}

bool cowl_test_ontology_get_id(void) {
    CowlIRI *expected_onto_iri = cowl_iri_from_static(test_onto_iri);
    cowl_assert_equal(iri, cowl_get_iri(onto), expected_onto_iri);

    CowlOntologyId id = cowl_ontology_get_id(onto);
    cowl_assert_equal(iri, id.iri, expected_onto_iri);
    cowl_release(expected_onto_iri);

    return true;
}

bool cowl_test_ontology_axiom_count(void) {
    ulib_uint axiom_count = cowl_ontology_axiom_count(onto, true);
    utest_assert_uint(axiom_count, ==, test_onto_axiom_count);
    return true;
}

bool cowl_test_ontology_imports_count(void) {
    ulib_uint imports_count = cowl_ontology_imports_count(onto, false);
    utest_assert_uint(imports_count, ==, test_onto_imports_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_type(void) {
    for (ulib_uint type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        ulib_uint expected_count = axiom_counts_by_type[type];
        ulib_uint count = cowl_ontology_axiom_count_for_type(onto, (CowlAxiomType)type, true);
        utest_assert_uint(count, ==, expected_count);
    }

    return true;
}

bool cowl_test_ontology_axiom_count_for_types(void) {
    ulib_uint expected = axiom_counts_by_type[COWL_AT_SUB_CLASS] +
                         axiom_counts_by_type[COWL_AT_OBJ_PROP_ASSERT] +
                         axiom_counts_by_type[COWL_AT_ANNOT_ASSERT];
    CowlAxiomFlags types = COWL_AF_SUB_CLASS | COWL_AF_OBJ_PROP_ASSERT | COWL_AF_ANNOT_ASSERT;
    ulib_uint count = cowl_ontology_axiom_count_for_types(onto, types, true);
    utest_assert_uint(count, ==, expected);

    expected = test_onto_axiom_count;
    count = cowl_ontology_axiom_count_for_types(onto, COWL_AF_ALL, true);
    utest_assert_uint(count, ==, expected);

    return true;
}

bool cowl_test_ontology_primitives_count(void) {
    for (ulib_uint i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        CowlPrimitiveFlags flags = cowl_primitive_flags_from_type((CowlPrimitiveType)i);
        ulib_uint c = cowl_ontology_primitives_count(onto, flags, true);
        utest_assert_uint(c, ==, test_primitives_count[i]);
    }
    return true;
}

static bool cowl_test_get_first_anon_ind(void *ctx, CowlAny *obj) {
    *((CowlAny **)ctx) = obj;
    return false;
}

bool cowl_test_ontology_axiom_count_for_primitive(void) {
    CowlAnyPrimitive *primitive = cowl_class_from_static(test_onto_iri test_class);
    ulib_uint count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_CLASS]);

    primitive = cowl_datatype_from_static(test_onto_iri test_datatype);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATATYPE]);

    primitive = cowl_obj_prop_from_static(test_onto_iri test_obj_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_OBJ_PROP]);

    primitive = cowl_data_prop_from_static(test_onto_iri test_data_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_DATA_PROP]);

    primitive = cowl_annot_prop_from_static(test_onto_iri test_annot_prop);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_ANNOT_PROP]);

    primitive = cowl_named_ind_from_static(test_onto_iri test_named_ind);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_NAMED_IND]);

    primitive = cowl_iri_from_static(test_onto_iri test_iri);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    cowl_release(primitive);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_IRI]);

    CowlIterator iter = { &primitive, cowl_test_get_first_anon_ind };
    cowl_ontology_iterate_primitives(onto, COWL_PF_ANON_IND, &iter, true);
    count = cowl_ontology_axiom_count_for_primitive(onto, primitive, true);
    utest_assert_uint(count, ==, test_primitive_axiom_count[COWL_PT_ANON_IND]);

    return true;
}

#define cowl_test_has_primitive(TYPE)                                                              \
    do {                                                                                           \
        CowlAnyPrimitive *p = cowl_##TYPE##_from_static(test_onto_iri test_##TYPE);                \
        utest_assert(cowl_ontology_has_primitive(onto, p, true));                                  \
        cowl_release(p);                                                                           \
        p = cowl_##TYPE##_from_static(test_onto_iri test_##TYPE "_not_present");                   \
        utest_assert_false(cowl_ontology_has_primitive(onto, p, true));                            \
        cowl_release(p);                                                                           \
    } while (0)

bool cowl_test_ontology_has_primitive(void) {
    cowl_test_has_primitive(class);
    cowl_test_has_primitive(datatype);
    cowl_test_has_primitive(named_ind);
    cowl_test_has_primitive(obj_prop);
    cowl_test_has_primitive(data_prop);
    cowl_test_has_primitive(annot_prop);
    cowl_test_has_primitive(iri);
    return true;
}

static CowlDatatypeDefAxiom *generate_datatype_def(char const *v1, char const *v2, char const *v3) {
    CowlDatatype *dt = cowl_datatype_from_static(test_onto_iri "DataOneOf");
    CowlLiteral *l1 = cowl_literal_from_string(ustring_null, ustring_wrap_buf(v1), ustring_null);
    CowlLiteral *l2 = cowl_literal_from_string(ustring_null, ustring_wrap_buf(v2), ustring_null);
    CowlLiteral *l3 = cowl_literal_from_string(ustring_null, ustring_wrap_buf(v3), ustring_null);
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

bool cowl_test_ontology_has_axiom(void) {
    CowlDatatypeDefAxiom *axiom = NULL;
    // DatatypeDefinition(:DataOneOf DataOneOf("DataOneOf_Literal1"^^xsd:string
    // "DataOneOf_Literal2"^^xsd:string "DataOneOf_Literal3"^^xsd:string))
    axiom = generate_datatype_def("DataOneOf_Literal3", "DataOneOf_Literal2", "DataOneOf_Literal1");
    utest_assert(cowl_ontology_has_axiom(onto, axiom, false));
    cowl_release(axiom);

    // DatatypeDefinition(:DataOneOf DataOneOf("DataOneOf_Literal1"^^xsd:string
    // "DataOneOf_Literal2"^^xsd:string "DataOneOf_Literal4"^^xsd:string))
    axiom = generate_datatype_def("DataOneOf_Literal4", "DataOneOf_Literal2", "DataOneOf_Literal1");
    utest_assert_false(cowl_ontology_has_axiom(onto, axiom, false));
    cowl_release(axiom);

    return true;
}
