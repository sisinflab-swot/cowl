/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_PRIVATE_H
#define COWL_READER_PRIVATE_H

#include "cowl_reader.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlReader) {
    CowlObject super;
    UIStream *stream;
    char const *stream_description;
    CowlOntology *ontology;
    void *state;
    CowlParser parser;
    CowlErrorHandler handler;
    CowlImportLoader loader;
};

COWL_END_DECLS

#endif // COWL_READER_PRIVATE_H
