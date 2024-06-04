/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OWL_VOCAB_PRIVATE_H
#define COWL_OWL_VOCAB_PRIVATE_H

#include "cowl_owl_vocab.h"
#include "cowl_ret.h"

COWL_BEGIN_DECLS

cowl_ret cowl_owl_vocab_init(void);
void cowl_owl_vocab_deinit(void);

COWL_END_DECLS

#endif // COWL_OWL_VOCAB_PRIVATE_H
