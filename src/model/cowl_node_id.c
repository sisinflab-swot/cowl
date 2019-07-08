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
#include "cowl_string.h"

CowlNodeID cowl_node_id_get_unique(void) {
    static CowlNodeID current = 0;
    return current++;
}

CowlString* cowl_node_id_to_string(CowlNodeID id) {
    return cowl_string_with_format("_:id%llu", id);
}
