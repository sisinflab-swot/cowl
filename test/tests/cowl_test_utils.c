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
#include "cowl_reader.h"

// Test import ontology

static char const test_import[] = "test_import.owl";

// Import loader

CowlOntology* cowl_test_load_import(cowl_unused void *ctx, cowl_unused CowlIRI *iri) {
    CowlReader *reader = cowl_reader_get();
    CowlOntology *onto = cowl_reader_read_path(reader, test_import);
    cowl_reader_release(reader);
    return onto;
}
