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
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_entity.h"
#include "cowl_iri.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"
#include "cowl_ontology.h"
#include "cowl_manager.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"

// Test data

#define test_onto_iri "http://visualdataweb.de/ontobench/ontology/1/"
#define test_class "Class1"
#define test_datatype "DataUnionOf_Datatype1"
#define test_obj_prop "equivalentObjectProperty_1"
#define test_data_prop "equivalentDataProperty_1"
#define test_annot_prop "customAnnotationProperty"
#define test_named_ind "AllDifferent_Individual1"

static CowlOntology *onto = NULL;

static ulib_uint const test_onto_imports_count = 1;
static ulib_uint const test_onto_axiom_count = 565;

static ulib_uint const test_onto_classes_count = 104;
static ulib_uint const test_onto_datatypes_count = 43;
static ulib_uint const test_onto_obj_props_count = 47;
static ulib_uint const test_onto_data_props_count = 72;
static ulib_uint const test_onto_annot_props_count = 25;
static ulib_uint const test_onto_named_inds_count = 18;
static ulib_uint const test_onto_anon_inds_count = 1;

static ulib_uint const test_class_axiom_count = 16;
static ulib_uint const test_datatype_axiom_count = 2;
static ulib_uint const test_obj_prop_axiom_count = 4;
static ulib_uint const test_data_prop_axiom_count = 4;
static ulib_uint const test_annot_prop_axiom_count = 2;
static ulib_uint const test_named_ind_axiom_count = 2;
static ulib_uint const test_anon_ind_axiom_count = 1;

static ulib_uint* test_onto_axiom_counts(void) {
    static ulib_uint counts[COWL_AT_COUNT] = { 0 };

    counts[COWL_AT_DECL] = 262;
    counts[COWL_AT_DATATYPE_DEF] = 2;
    counts[COWL_AT_SUB_CLASS] = 33;
    counts[COWL_AT_EQUIV_CLASSES] = 4;
    counts[COWL_AT_DISJ_CLASSES] = 4;
    counts[COWL_AT_DISJ_UNION] = 1;
    counts[COWL_AT_CLASS_ASSERT] = 2;
    counts[COWL_AT_SAME_IND] = 1;
    counts[COWL_AT_DIFF_IND] = 1;
    counts[COWL_AT_OBJ_PROP_ASSERT] = 1;
    counts[COWL_AT_NEG_OBJ_PROP_ASSERT] = 1;
    counts[COWL_AT_DATA_PROP_ASSERT] = 1;
    counts[COWL_AT_NEG_DATA_PROP_ASSERT] = 1;
    counts[COWL_AT_SUB_OBJ_PROP] = 1;
    counts[COWL_AT_SUB_OBJ_PROP_CHAIN] = 1;
    counts[COWL_AT_INV_OBJ_PROP] = 1;
    counts[COWL_AT_EQUIV_OBJ_PROP] = 1;
    counts[COWL_AT_DISJ_OBJ_PROP] = 2;
    counts[COWL_AT_FUNC_OBJ_PROP] = 1;
    counts[COWL_AT_INV_FUNC_OBJ_PROP] = 1;
    counts[COWL_AT_SYMM_OBJ_PROP] = 1;
    counts[COWL_AT_ASYMM_OBJ_PROP] = 1;
    counts[COWL_AT_TRANS_OBJ_PROP] = 1;
    counts[COWL_AT_REFL_OBJ_PROP] = 1;
    counts[COWL_AT_IRREFL_OBJ_PROP] = 1;
    counts[COWL_AT_OBJ_PROP_DOMAIN] = 39;
    counts[COWL_AT_OBJ_PROP_RANGE] = 39;
    counts[COWL_AT_SUB_DATA_PROP] = 1;
    counts[COWL_AT_EQUIV_DATA_PROP] = 1;
    counts[COWL_AT_DISJ_DATA_PROP] = 2;
    counts[COWL_AT_FUNC_DATA_PROP] = 1;
    counts[COWL_AT_DATA_PROP_DOMAIN] = 66;
    counts[COWL_AT_DATA_PROP_RANGE] = 66;
    counts[COWL_AT_HAS_KEY] = 1;
    counts[COWL_AT_ANNOT_ASSERT] = 19;
    counts[COWL_AT_SUB_ANNOT_PROP] = 1;
    counts[COWL_AT_ANNOT_PROP_DOMAIN] = 1;
    counts[COWL_AT_ANNOT_PROP_RANGE] = 1;

    return counts;
}

// Init/deinit

bool cowl_test_ontology_init(void) {
    CowlManager *manager = cowl_manager_get();
    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_manager_set_import_loader(manager, loader);
    onto = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    cowl_manager_release(manager);
    utest_assert_critical(onto);
    return true;
}

bool cowl_test_ontology_deinit(void) {
    cowl_ontology_release(onto);
    return true;
}

// Tests

bool cowl_test_ontology_get_id(void) {
    CowlOntologyId id = cowl_ontology_get_id(onto);
    utest_assert_not_null(id.ontology_iri);

    CowlIRI *expected_onto_iri = cowl_iri_from_static(test_onto_iri);
    cowl_assert_equal(iri, id.ontology_iri, expected_onto_iri);
    cowl_iri_release(expected_onto_iri);

    return true;
}

bool cowl_test_ontology_axiom_count(void) {
    ulib_uint axiom_count = cowl_ontology_axiom_count(onto);
    utest_assert_uint(axiom_count, ==, test_onto_axiom_count);
    return true;
}

bool cowl_test_ontology_imports_count(void) {
    ulib_uint imports_count = cowl_ontology_imports_count(onto);
    utest_assert_uint(imports_count, ==, test_onto_imports_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_type(void) {
    ulib_uint *expected_axiom_counts = test_onto_axiom_counts();

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        ulib_uint expected_count = expected_axiom_counts[type];
        ulib_uint count = cowl_ontology_axiom_count_for_type(onto, type);
        utest_assert_uint(count, ==, expected_count);
    }

    return true;
}

bool cowl_test_ontology_class_count(void) {
    ulib_uint count = cowl_ontology_classes_count(onto);
    utest_assert_uint(count, ==, test_onto_classes_count);
    return true;
}

bool cowl_test_ontology_datatypes_count(void) {
    ulib_uint count = cowl_ontology_datatypes_count(onto);
    utest_assert_uint(count, ==, test_onto_datatypes_count);
    return true;
}

bool cowl_test_ontology_obj_props_count(void) {
    ulib_uint count = cowl_ontology_obj_props_count(onto);
    utest_assert_uint(count, ==, test_onto_obj_props_count);
    return true;
}

bool cowl_test_ontology_data_props_count(void) {
    ulib_uint count = cowl_ontology_data_props_count(onto);
    utest_assert_uint(count, ==, test_onto_data_props_count);
    return true;
}

bool cowl_test_ontology_annot_props_count(void) {
    ulib_uint count = cowl_ontology_annot_props_count(onto);
    utest_assert_uint(count, ==, test_onto_annot_props_count);
    return true;
}

bool cowl_test_ontology_named_inds_count(void) {
    ulib_uint count = cowl_ontology_named_inds_count(onto);
    utest_assert_uint(count, ==, test_onto_named_inds_count);
    return true;
}

bool cowl_test_ontology_anon_inds_count(void) {
    ulib_uint count = cowl_ontology_anon_inds_count(onto);
    utest_assert_uint(count, ==, test_onto_anon_inds_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_class(void) {
    CowlClass *cls = cowl_class_from_static(test_onto_iri test_class);
    ulib_uint count = cowl_ontology_axiom_count_for_class(onto, cls);
    cowl_class_release(cls);
    utest_assert_uint(count, ==, test_class_axiom_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_datatype(void) {
    CowlDatatype *dt = cowl_datatype_from_static(test_onto_iri test_datatype);
    ulib_uint count = cowl_ontology_axiom_count_for_datatype(onto, dt);
    cowl_datatype_release(dt);
    utest_assert_uint(count, ==, test_datatype_axiom_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_obj_prop(void) {
    CowlObjProp *prop = cowl_obj_prop_from_static(test_onto_iri test_obj_prop);
    ulib_uint count = cowl_ontology_axiom_count_for_obj_prop(onto, prop);
    cowl_obj_prop_release(prop);
    utest_assert_uint(count, ==, test_obj_prop_axiom_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_data_prop(void) {
    CowlDataProp *prop = cowl_data_prop_from_static(test_onto_iri test_data_prop);
    ulib_uint count = cowl_ontology_axiom_count_for_data_prop(onto, prop);
    cowl_data_prop_release(prop);
    utest_assert_uint(count, ==, test_data_prop_axiom_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_annot_prop(void) {
    CowlAnnotProp *prop = cowl_annot_prop_from_static(test_onto_iri test_annot_prop);
    ulib_uint count = cowl_ontology_axiom_count_for_annot_prop(onto, prop);
    cowl_annot_prop_release(prop);
    utest_assert_uint(count, ==, test_annot_prop_axiom_count);
    return true;
}

bool cowl_test_ontology_axiom_count_for_named_ind(void) {
    CowlNamedInd *ind = cowl_named_ind_from_static(test_onto_iri test_named_ind);
    ulib_uint count = cowl_ontology_axiom_count_for_named_ind(onto, ind);
    cowl_named_ind_release(ind);
    utest_assert_uint(count, ==, test_named_ind_axiom_count);
    return true;
}

#define cowl_test_has_entity(TYPE) do {                                                             \
    CowlEntity *entity = (CowlEntity *)cowl_##TYPE##_from_static(test_onto_iri test_##TYPE);        \
    utest_assert(cowl_ontology_has_entity(onto, entity));                                           \
    cowl_entity_release(entity);                                                                    \
    entity = (CowlEntity *)cowl_##TYPE##_from_static(test_onto_iri test_##TYPE "_not_present");     \
    utest_assert_false(cowl_ontology_has_entity(onto, entity));                                     \
    cowl_entity_release(entity);                                                                    \
} while (0)

bool cowl_test_ontology_has_entity(void) {
    cowl_test_has_entity(class);
    cowl_test_has_entity(datatype);
    cowl_test_has_entity(named_ind);
    cowl_test_has_entity(obj_prop);
    cowl_test_has_entity(data_prop);
    cowl_test_has_entity(annot_prop);
    return true;
}

static bool cowl_test_get_first_anon_ind(void *ctx, void *obj) {
    *((CowlAnonInd**)ctx) = obj;
    return false;
}

bool cowl_test_ontology_axiom_count_for_anon_ind(void) {
    CowlAnonInd *ind = NULL;
    CowlIterator iter = cowl_iterator_init(&ind, cowl_test_get_first_anon_ind);
    cowl_ontology_iterate_anon_inds(onto, &iter);

    ulib_uint count = cowl_ontology_axiom_count_for_anon_ind(onto, ind);
    utest_assert_uint(count, ==, test_anon_ind_axiom_count);

    return true;
}
