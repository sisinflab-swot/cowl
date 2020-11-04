/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_version_tests.h"
#include "cowl_test_utils.h"
#include "cowl_version.h"

bool cowl_test_version(void) {
    CowlVersion v = cowl_api_get_version();
    cowl_assert(!(v.major == 0 && v.minor == 0 && v.patch == 0), "Version must not be 0.0.0");
    return true;
}
