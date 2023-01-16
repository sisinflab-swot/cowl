/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_version_tests.h"
#include "cowl_version.h"

bool cowl_test_version(void) {
    UVersion v = cowl_get_version(), zero = { 0 };
    utest_assert_int(uversion_compare(v, zero), ==, 1);
    return true;
}
