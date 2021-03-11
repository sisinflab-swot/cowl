/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_PRIVATE_H
#define COWL_PARSER_PRIVATE_H

#include "cowl_parser.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlParser) {
    CowlObject super;
    CowlSubParser const *sp;
    CowlInputStream *stream;
    CowlOntology *ontology;
    void *state;
    CowlErrorHandler handler;
    CowlImportLoader loader;
};

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
