/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_axiom.h"
#include "cowl_iterator_private.h"
#include "cowl_vector.h"

static inline bool index_allowed(unsigned n, unsigned i, CowlPosition position) {
    CowlPosition const positions[][3] = {
        { COWL_PS_ANY },
        { COWL_PS_LEFT, COWL_PS_RIGHT },
        { COWL_PS_LEFT, COWL_PS_MIDDLE, COWL_PS_RIGHT },
    };
    return ubit_is_any_set(COWL_PS, position, positions[n - 1][i]);
}

bool cowl_axiom_has_operand(CowlAnyAxiom *axiom, CowlAny *operand, CowlPosition position) {
    unsigned n;
    CowlAny **fields = cowl_get_fields(axiom, &n);

    for (unsigned i = 0; i < n; ++i) {
        if (!index_allowed(n, i, position)) continue;
        CowlAny *op = fields[i];
        if (cowl_get_type(op) == COWL_OT_VECTOR) {
            cowl_vector_foreach (op, obj) {
                if (cowl_equals(operand, *obj.item)) return true;
            }
        } else {
            if (cowl_equals(operand, op)) return true;
        }
    }

    return false;
}

bool cowl_axiom_iterate_operands(CowlAnyAxiom *axiom, CowlPosition position, CowlIterator *iter) {
    unsigned n;
    CowlAny **fields = cowl_get_fields(axiom, &n);

    for (unsigned i = 0; i < n; ++i) {
        if (!index_allowed(n, i, position)) continue;
        CowlAny *op = fields[i];
        if (cowl_get_type(op) == COWL_OT_VECTOR) {
            cowl_vector_foreach (op, obj) {
                if (!cowl_iterate(iter, *obj.item)) return false;
            }
        } else {
            if (!cowl_iterate(iter, op)) return false;
        }
    }

    return true;
}
