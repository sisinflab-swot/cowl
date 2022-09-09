/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_test_utils.h"
#include "cowl_manager.h"

// Test import ontology

#define COWL_TEST_IMPORT "test_import.owl"

// Import loader

CowlOntology* cowl_test_load_import(void *ctx, cowl_unused CowlIRI *iri) {
    return cowl_manager_read_path((CowlManager *)ctx, ustring_literal(COWL_TEST_IMPORT));
}
