/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#ifndef COWL_READER_EX_PRIVATE_H
#define COWL_READER_EX_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_object_private.h"
#include "cowl_reader.h" // IWYU pragma: export
#include <stddef.h>

COWL_BEGIN_DECLS

struct CowlReader {
    CowlObject super;
    CowlReaderImpl impl;
};

void cowl_reader_free(CowlReader *reader);

COWL_END_DECLS

#endif // COWL_READER_EX_PRIVATE_H
