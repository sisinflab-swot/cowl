/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_version.h"
#include "cowl_string.h"

#ifndef COWL_VERSION_MAJOR
    #define COWL_VERSION_MAJOR 0
#endif

#ifndef COWL_VERSION_MINOR
    #define COWL_VERSION_MINOR 0
#endif

#ifndef COWL_VERSION_PATCH
    #define COWL_VERSION_PATCH 0
#endif

static UVersion version = {
    .major = COWL_VERSION_MAJOR,
    .minor = COWL_VERSION_MINOR,
    .patch = COWL_VERSION_PATCH
};

UVersion cowl_api_get_version(void) {
    return version;
}

CowlString* cowl_api_get_version_string(void) {
    return cowl_string_with_format("%u.%u.%u", version.major, version.minor, version.patch);
}
