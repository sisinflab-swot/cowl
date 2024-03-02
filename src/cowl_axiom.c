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
#include "cowl_primitive_private.h"
#include "cowl_vector.h"

bool cowl_axiom_has_operand(CowlAnyAxiom *axiom, CowlAny *operand, CowlPosition position) {
    CowlIterator iter = cowl_iterator_contains(operand);
    return !cowl_axiom_iterate_operands(axiom, position, &iter);
}

static bool has_iri(void *iri, CowlAny *object) {
    return !cowl_has_iri(object, iri);
}

bool cowl_axiom_has_operand_with_iri(CowlAnyAxiom *axiom, CowlIRI *iri, CowlPosition position) {
    CowlIterator iter = { .ctx = iri, .for_each = has_iri };
    return !cowl_axiom_iterate_operands(axiom, position, &iter);
}

static inline bool index_allowed(unsigned n, unsigned i, CowlPosition position) {
    CowlPosition const positions[][3] = {
        { COWL_PS_ANY },
        { COWL_PS_LEFT, COWL_PS_RIGHT },
        { COWL_PS_LEFT, COWL_PS_MIDDLE, COWL_PS_RIGHT },
    };
    return ubit_is_any_set(COWL_PS, position, positions[n - 1][i]);
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

static bool operand_has_primitive(void *primitive, CowlAny *operand) {
    if (cowl_primitive_equals(operand, primitive)) return false;
    return !cowl_has_primitive(operand, primitive);
}

bool cowl_axiom_has_primitive(CowlAnyAxiom *axiom, CowlPosition position,
                              CowlAnyPrimitive *primitive) {
    if (position == COWL_PS_ANY) return cowl_has_primitive(axiom, primitive);
    CowlIterator iter = { .ctx = primitive, .for_each = operand_has_primitive };
    return !cowl_axiom_iterate_operands(axiom, position, &iter);
}
