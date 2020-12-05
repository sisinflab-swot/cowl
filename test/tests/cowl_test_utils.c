/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_test_utils.h"
#include "cowl_parser.h"

// Test import ontology

static char const test_import[] = "test_import.owl";

// Imports loader

CowlOntology* cowl_test_load_import(cowl_unused void *ctx, cowl_unused CowlIRI *iri) {
    CowlParser *parser = cowl_parser_get();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, test_import);
    cowl_parser_release(parser);
    return onto;
}
