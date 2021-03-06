/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_node_id.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

CowlNodeID cowl_node_id_get_unique(void) {
    static CowlNodeID current = COWL_NODE_ID_NULL;
    return ++current;
}

CowlString* cowl_node_id_to_string(CowlNodeID id)
    COWL_TO_STRING_IMPL(node_id, id)
