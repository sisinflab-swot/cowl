/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DISJ_UNION_AXIOM_PRIVATE_H
#define COWL_DISJ_UNION_AXIOM_PRIVATE_H

#include "cowl_disj_union_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlDisjUnionAxiom,
    CowlClass *cls;
    CowlObjectTable *disjoints;
);

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_PRIVATE_H
