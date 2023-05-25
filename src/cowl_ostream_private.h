/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OSTREAM_PRIVATE_H
#define COWL_OSTREAM_PRIVATE_H

#include "cowl_object_private.h"
#include "cowl_ontology_header.h"
#include "cowl_ostream.h"
#include "cowl_sym_table_private.h"

COWL_BEGIN_DECLS

struct CowlOStream {
    CowlObject super;
    CowlSymTable st;
    CowlManager *manager;
    UOStream *stream;
};

CowlOStream *cowl_ostream(CowlManager *manager, UOStream *stream);
void cowl_ostream_free(CowlOStream *stream);

COWL_END_DECLS

#endif // COWL_OSTREAM_PRIVATE_H
