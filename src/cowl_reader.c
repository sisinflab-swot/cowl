/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_reader.h"
#include <stddef.h>

CowlReader p_cowl_reader_invalid(void) {
    return (CowlReader){ 0 };
}

void cowl_reader_free_ctx(CowlReader *reader) {
    if (!(reader->free && reader->ctx)) return;
    reader->free(reader->ctx);
    reader->ctx = NULL;
}
