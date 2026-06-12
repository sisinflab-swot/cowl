/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2026 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#ifndef COWL_AXIOM_TESTS_H
#define COWL_AXIOM_TESTS_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

void cowl_test_axiom_equals(void);
void cowl_test_axiom_operands(void);
void cowl_test_axiom_primitives(void);

#define COWL_AXIOM_TESTS                                                                           \
    cowl_test_axiom_equals, cowl_test_axiom_operands, cowl_test_axiom_primitives

COWL_END_DECLS

#endif // COWL_AXIOM_TESTS_H
