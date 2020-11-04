/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_axiom_set.h"
#include "cowl_axiom.h"

UHASH_IMPL(CowlAxiomSet, cowl_axiom_hash, cowl_axiom_equals)

void cowl_axiom_set_free(UHash(CowlAxiomSet) *set) {
    if (!set) return;
    uhash_foreach_key(CowlAxiomSet, set, axiom, cowl_axiom_release(axiom));
    uhash_free(CowlAxiomSet, set);
}
