/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_AXIOM_VEC_H
#define COWL_AXIOM_VEC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAxiom);

typedef CowlAxiom* CowlAxiomPtr;
UVEC_DECL_EQUATABLE(CowlAxiomPtr)

COWL_END_DECLS

#endif // COWL_AXIOM_VEC_H
