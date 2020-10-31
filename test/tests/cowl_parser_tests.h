/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_TESTS_H
#define COWL_PARSER_TESTS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_parser_lifecycle(void);
bool cowl_test_parser_parse_ontology(void);

#define COWL_PARSER_TESTS                                                                           \
    cowl_test_parser_lifecycle,                                                                     \
    cowl_test_parser_parse_ontology

COWL_END_DECLS

#endif // COWL_PARSER_TESTS_H
