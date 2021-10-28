/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H
#define COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H

#include "cowl_data_prop_assert_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlDataPropAssertAxiom,
    CowlIndividual *subject;
    CowlDataPropExp *prop;
    CowlLiteral *object;
);

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H
