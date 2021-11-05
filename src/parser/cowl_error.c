/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_error.h"
#include "cowl_template.h"

CowlString* cowl_error_to_string(CowlError const *error)
    COWL_TO_STRING_IMPL(error, error)
