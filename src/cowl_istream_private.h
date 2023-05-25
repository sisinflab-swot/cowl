/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ISTREAM_PRIVATE_H
#define COWL_ISTREAM_PRIVATE_H

#include "cowl_istream.h"
#include "cowl_istream_config.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);

struct CowlIStream {
    CowlObject super;
    CowlIStreamConfig config;
    CowlSymTable *st;
    CowlManager *manager;
};

CowlIStream *cowl_istream(CowlManager *manager, CowlIStreamConfig config);
CowlIStream *cowl_istream_to_ontology(CowlOntology *onto);
void cowl_istream_free(CowlIStream *stream);

COWL_END_DECLS

#endif // COWL_ISTREAM_PRIVATE_H
