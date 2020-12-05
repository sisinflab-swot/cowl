/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_tests.h"
#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_iri.h"
#include "cowl_named_ind.h"
#include "cowl_obj_prop.h"
#include "cowl_ontology.h"
#include "cowl_ontology_id.h"
#include "cowl_parser.h"
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

static cowl_uint const test_onto_imports_count = 1;
static cowl_uint const test_onto_axiom_count = 565;

static cowl_uint const test_onto_classes_count = 104;
static cowl_uint const test_onto_datatypes_count = 43;
static cowl_uint const test_onto_obj_props_count = 47;
static cowl_uint const test_onto_data_props_count = 72;
static cowl_uint const test_onto_annot_props_count = 25;
static cowl_uint const test_onto_named_inds_count = 18;
static cowl_uint const test_onto_anon_inds_count = 1;

static cowl_uint const test_class_axiom_count = 16;
static cowl_uint const test_datatype_axiom_count = 2;
static cowl_uint const test_obj_prop_axiom_count = 4;
static cowl_uint const test_data_prop_axiom_count = 4;
static cowl_uint const test_annot_prop_axiom_count = 2;
static cowl_uint const test_named_ind_axiom_count = 2;
static cowl_uint const test_anon_ind_axiom_count = 1;

static cowl_uint* test_onto_axiom_counts(void) {
    static cowl_uint counts[COWL_AT_COUNT] = { 0 };

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
    CowlParser *parser = cowl_parser_get();
    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_parser_set_import_loader(parser, loader);
    onto = cowl_parser_parse_ontology(parser, COWL_TEST_ONTOLOGY);
    cowl_parser_release(parser);
    cowl_assert_critical(onto, "Ontology parsing must complete without errors.");
    return true;
}

bool cowl_test_ontology_deinit(void) {
    cowl_ontology_release(onto);
    return true;
}

// Tests

bool cowl_test_ontology_get_id(void) {
    CowlOntologyID id = cowl_ontology_get_id(onto);
    CowlIRI *expected_onto_iri = cowl_iri_from_static(test_onto_iri);
    cowl_assert_equal(iri, id.ontology_iri, expected_onto_iri, "Ontology IRI");
    cowl_iri_release(expected_onto_iri);

    return true;
}

bool cowl_test_ontology_axiom_count(void) {
    cowl_uint axiom_count = cowl_ontology_axiom_count(onto);
    cowl_assert_equal_int(axiom_count, test_onto_axiom_count, "Axiom count");
    return true;
}

bool cowl_test_ontology_imports_count(void) {
    cowl_uint imports_count = cowl_ontology_imports_count(onto);
    cowl_assert_equal_int(imports_count, test_onto_imports_count, "Imports count");
    return true;
}

bool cowl_test_ontology_axiom_count_for_type(void) {
    cowl_uint *expected_axiom_counts = test_onto_axiom_counts();

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_uint expected_count = expected_axiom_counts[type];
        cowl_uint count = cowl_ontology_axiom_count_for_type(onto, type);
        cowl_assert_equal_int(count, expected_count, "Axiom count for type %d", type);
    }

    return true;
}

bool cowl_test_ontology_class_count(void) {
    cowl_uint count = cowl_ontology_classes_count(onto);
    cowl_assert_equal_int(count, test_onto_classes_count, "Number of classes");
    return true;
}

bool cowl_test_ontology_datatypes_count(void) {
    cowl_uint count = cowl_ontology_datatypes_count(onto);
    cowl_assert_equal_int(count, test_onto_datatypes_count, "Number of datatypes");
    return true;
}

bool cowl_test_ontology_obj_props_count(void) {
    cowl_uint count = cowl_ontology_obj_props_count(onto);
    cowl_assert_equal_int(count, test_onto_obj_props_count, "Number of object properties");
    return true;
}

bool cowl_test_ontology_data_props_count(void) {
    cowl_uint count = cowl_ontology_data_props_count(onto);
    cowl_assert_equal_int(count, test_onto_data_props_count, "Number of data properties");
    return true;
}

bool cowl_test_ontology_annot_props_count(void) {
    cowl_uint count = cowl_ontology_annot_props_count(onto);
    cowl_assert_equal_int(count, test_onto_annot_props_count, "Number of annotation properties");
    return true;
}

bool cowl_test_ontology_named_inds_count(void) {
    cowl_uint count = cowl_ontology_named_inds_count(onto);
    cowl_assert_equal_int(count, test_onto_named_inds_count, "Number of named individuals");
    return true;
}

bool cowl_test_ontology_anon_inds_count(void) {
    cowl_uint count = cowl_ontology_anon_inds_count(onto);
    cowl_assert_equal_int(count, test_onto_anon_inds_count, "Number of anonymous individuals");
    return true;
}

bool cowl_test_ontology_axiom_count_for_class(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_class);
    CowlClass *cls = cowl_class_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_class(onto, cls);
    cowl_class_release(cls);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_class_axiom_count, "Number of axioms for " test_class);
    return true;
}

bool cowl_test_ontology_axiom_count_for_datatype(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_datatype);
    CowlDatatype *dt = cowl_datatype_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_datatype(onto, dt);
    cowl_datatype_release(dt);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_datatype_axiom_count, "Number of axioms for " test_datatype);
    return true;
}

bool cowl_test_ontology_axiom_count_for_obj_prop(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_obj_prop);
    CowlObjProp *prop = cowl_obj_prop_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_obj_prop(onto, prop);
    cowl_obj_prop_release(prop);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_obj_prop_axiom_count, "Number of axioms for " test_obj_prop);
    return true;
}

bool cowl_test_ontology_axiom_count_for_data_prop(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_data_prop);
    CowlDataProp *prop = cowl_data_prop_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_data_prop(onto, prop);
    cowl_data_prop_release(prop);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_data_prop_axiom_count,
                          "Number of axioms for " test_data_prop);
    return true;
}

bool cowl_test_ontology_axiom_count_for_annot_prop(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_annot_prop);
    CowlAnnotProp *prop = cowl_annot_prop_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_annot_prop(onto, prop);
    cowl_annot_prop_release(prop);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_annot_prop_axiom_count,
                          "Number of axioms for " test_annot_prop);
    return true;
}

bool cowl_test_ontology_axiom_count_for_named_ind(void) {
    CowlIRI *iri = cowl_iri_from_static(test_onto_iri test_named_ind);
    CowlNamedInd *ind = cowl_named_ind_get(iri);
    cowl_uint count = cowl_ontology_axiom_count_for_named_ind(onto, ind);
    cowl_named_ind_release(ind);
    cowl_iri_release(iri);
    cowl_assert_equal_int(count, test_named_ind_axiom_count,
                          "Number of axioms for " test_named_ind);
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

    cowl_uint count = cowl_ontology_axiom_count_for_anon_ind(onto, ind);
    cowl_assert_equal_int(count, test_anon_ind_axiom_count,
                          "Number of axioms for the only anonymous individual");

    return true;
}
