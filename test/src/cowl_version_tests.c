/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_version_tests.h"
#include "cowl.h"
#include "ulib.h"

void cowl_test_version(void) {
    UVersion v = cowl_get_version();
    UVersion zero = { 0 };
    utest_assert_int(uversion_compare(v, zero), ==, 1);
}
