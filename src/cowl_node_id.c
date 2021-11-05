/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_node_id.h"
#include "cowl_template.h"

CowlString* cowl_node_id_to_string(CowlNodeId id)
    COWL_TO_STRING_IMPL(node_id, id)
