/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_RDF_VOCAB_PRIVATE_H
#define COWL_RDF_VOCAB_PRIVATE_H

#include "cowl_rdf_vocab.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

cowl_ret cowl_rdf_vocab_init(void);
void cowl_rdf_vocab_deinit(void);

COWL_END_DECLS

#endif // COWL_RDF_VOCAB_PRIVATE_H
