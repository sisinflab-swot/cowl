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
#include "cowl_iri.h"
#include "cowl_ontology.h"
#include "cowl_ontology_id.h"
#include "cowl_parser.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"

// Test data

static char const test_onto_iri[] = "http://visualdataweb.de/ontobench/ontology/1/";
static cowl_uint_t const test_onto_imports_count = 1;
static cowl_uint_t const test_onto_axiom_count = 565;

static cowl_uint_t* test_onto_axiom_counts(void) {
    static cowl_uint_t counts[COWL_AT_COUNT] = { 0 };

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

// Utils

static CowlOntology* cowl_test_ontology_get(void) {
    static CowlOntology *onto = NULL;

    if (!onto) {
        CowlParser *parser = cowl_parser_get();
        CowlImportsLoader loader = cowl_imports_loader_init(NULL, cowl_test_load_import, NULL);
        cowl_parser_set_imports_loader(parser, loader);
        onto = cowl_parser_parse_ontology(parser, COWL_TEST_ONTOLOGY, NULL);
        cowl_parser_release(parser);
    }

    return onto;
}

// Tests

bool cowl_test_ontology_get_id(void) {
    CowlOntologyID *id = cowl_ontology_get_id(cowl_test_ontology_get());
    CowlIRI *onto_iri = cowl_ontology_id_get_onto_iri(id);

    CowlIRI *expected_onto_iri = cowl_iri_from_static(test_onto_iri);
    cowl_assert_equal(iri, onto_iri, expected_onto_iri, "Ontology IRI");
    cowl_iri_release(expected_onto_iri);

    return true;
}

bool cowl_test_ontology_axiom_count(void) {
    cowl_uint_t axiom_count = cowl_ontology_axiom_count(cowl_test_ontology_get());
    cowl_assert_equal_int(axiom_count, test_onto_axiom_count, "Axiom count");
    return true;
}

bool cowl_test_ontology_imports_count(void) {
    cowl_uint_t imports_count = cowl_ontology_imports_count(cowl_test_ontology_get());
    cowl_assert_equal_int(imports_count, test_onto_imports_count, "Imports count");
    return true;
}

bool cowl_test_ontology_axiom_count_for_type(void) {
    CowlOntology *onto = cowl_test_ontology_get();
    cowl_uint_t *expected_axiom_counts = test_onto_axiom_counts();

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_uint_t expected_count = expected_axiom_counts[type];
        cowl_uint_t count = cowl_ontology_axiom_count_for_type(onto, type);
        cowl_assert_equal_int(count, expected_count, "Axiom count for type %d", type);
    }

    return true;
}
