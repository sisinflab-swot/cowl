/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_prop_range_axiom_private.h"
#include "cowl_annot_prop.h"
#include "cowl_iri.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_alloc(CowlAnnotProp *prop,
                                                                  CowlIRI *range,
                                                                  CowlAnnotationVec *annot) {
    CowlAnnotPropRangeAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint hash = cowl_axiom_hash_2(COWL_HASH_INIT_ANNOT_PROP_RANGE_AXIOM, annot,
                                       cowl_annot_prop_hash(prop),
                                       cowl_iri_hash(range));

    cowl_axiom_init(CowlAnnotPropRangeAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_ANNOT_PROP_RANGE, hash, annot),
        .prop = cowl_annot_prop_retain(prop),
        .range = cowl_iri_retain(range)
    );

    return axiom;
}

static void cowl_annot_prop_range_axiom_free(CowlAnnotPropRangeAxiom *axiom) {
    if (!axiom) return;
    cowl_annot_prop_release(axiom->prop);
    cowl_iri_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_get(CowlAnnotProp *prop, CowlIRI *range,
                                                         CowlAnnotationVec *annot) {
    if (!(prop && range)) return NULL;
    return cowl_annot_prop_range_axiom_alloc(prop, range, annot);
}

CowlAnnotPropRangeAxiom* cowl_annot_prop_range_axiom_retain(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_object_incr_ref(axiom);
}

void cowl_annot_prop_range_axiom_release(CowlAnnotPropRangeAxiom *axiom) {
    if (axiom && !cowl_object_decr_ref(axiom)) {
        cowl_annot_prop_range_axiom_free(axiom);
    }
}

CowlAnnotProp* cowl_annot_prop_range_axiom_get_prop(CowlAnnotPropRangeAxiom *axiom) {
    return axiom->prop;
}

CowlIRI* cowl_annot_prop_range_axiom_get_range(CowlAnnotPropRangeAxiom *axiom) {
    return axiom->range;
}

CowlAnnotationVec* cowl_annot_prop_range_axiom_get_annot(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_annot_prop_range_axiom_to_string(CowlAnnotPropRangeAxiom *axiom)
    COWL_TO_STRING_IMPL(annot_prop_range_axiom, axiom)

bool cowl_annot_prop_range_axiom_equals(CowlAnnotPropRangeAxiom *lhs,
                                        CowlAnnotPropRangeAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_iri_equals(lhs->range, rhs->range) &&
                                  cowl_annot_prop_equals(lhs->prop, rhs->prop));
}

cowl_uint cowl_annot_prop_range_axiom_hash(CowlAnnotPropRangeAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_annot_prop_range_axiom_iterate_primitives(CowlAnnotPropRangeAxiom *axiom,
                                                    CowlIterator *iter, CowlPrimitiveFlags flags) {
    return (cowl_annot_prop_iterate_primitives(axiom->prop, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
