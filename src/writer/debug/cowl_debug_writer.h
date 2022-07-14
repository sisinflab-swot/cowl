/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DEBUG_WRITER_H
#define COWL_DEBUG_WRITER_H

#include "cowl_writer.h"

COWL_BEGIN_DECLS

cowl_ret cowl_debug_write(UOStream *stream, void *object);
cowl_ret cowl_debug_write_ontology(void *state, UOStream *stream, CowlEditor *editor);

COWL_END_DECLS

#endif // COWL_DEBUG_WRITER_H
