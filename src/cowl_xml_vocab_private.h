/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_XML_VOCAB_PRIVATE_H
#define COWL_XML_VOCAB_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_ret.h"
#include "cowl_xml_vocab.h" // IWYU pragma: export

COWL_BEGIN_DECLS

cowl_ret cowl_xml_vocab_init(void);
void cowl_xml_vocab_deinit(void);

COWL_END_DECLS

#endif // COWL_XML_VOCAB_PRIVATE_H
