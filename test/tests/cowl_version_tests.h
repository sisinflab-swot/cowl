/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VERSION_TESTS_H
#define COWL_VERSION_TESTS_H

#include "cowl_attrs.h"
#include <stdbool.h>

COWL_BEGIN_DECLS

bool cowl_test_version(void);

#define COWL_VERSION_TESTS cowl_test_version

COWL_END_DECLS

#endif // COWL_VERSION_TESTS_H
