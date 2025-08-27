/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_WRITER_EX_PRIVATE_H
#define COWL_WRITER_EX_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_object_private.h"
#include "cowl_writer.h" // IWYU pragma: export

COWL_BEGIN_DECLS

struct CowlWriter {
    CowlObject super;
    CowlWriterImpl impl;
};

void cowl_writer_free(CowlWriter *writer);

COWL_END_DECLS

#endif // COWL_WRITER_EX_PRIVATE_H
