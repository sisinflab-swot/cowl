/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STREAM_PRIVATE_H
#define COWL_STREAM_PRIVATE_H

#include "cowl_object_private.h"
#include "cowl_stream.h"
#include "cowl_stream_config.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);

struct CowlStream {
    CowlObject super;
    CowlStreamConfig config;
    CowlSymTable *st;
    CowlManager *manager;
};

CowlStream* cowl_stream(CowlManager *manager, CowlStreamConfig config);
CowlStream* cowl_stream_to_ontology(CowlOntology *onto);
void cowl_stream_release(CowlStream *stream);

COWL_END_DECLS

#endif // COWL_STREAM_PRIVATE_H
