/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_datatype_def_axiom_private.h"
#include "cowl_data_range.h"
#include "cowl_datatype.h"
#include "cowl_str_buf.h"
#include "cowl_template.h"

static CowlDatatypeDefAxiom* cowl_datatype_def_axiom_alloc(CowlDatatype *dt,
                                                           CowlDataRange *range,
                                                           CowlAnnotationVec *annot) {
    CowlDatatypeDefAxiom *axiom = cowl_axiom_alloc(axiom, annot);
    if (!axiom) return NULL;

    cowl_uint_t hash = cowl_axiom_hash_2(COWL_HASH_INIT_DATATYPE_DEF_AXIOM, annot,
                                         cowl_datatype_hash(dt),
                                         cowl_data_range_hash(range));

    cowl_axiom_init(CowlDatatypeDefAxiom, axiom, annot,
        .super = COWL_AXIOM_INIT(COWL_AT_DATATYPE_DEF, hash, annot),
        .datatype = cowl_datatype_retain(dt),
        .range = cowl_data_range_retain(range)
    );

    return axiom;
}

static void cowl_datatype_def_axiom_free(CowlDatatypeDefAxiom *axiom) {
    if (!axiom) return;
    cowl_datatype_release(axiom->datatype);
    cowl_data_range_release(axiom->range);
    cowl_axiom_free(axiom);
}

CowlDatatypeDefAxiom* cowl_datatype_def_axiom_get(CowlDatatype *dt, CowlDataRange *range,
                                                  CowlAnnotationVec *annot) {
    if (!(dt && range)) return NULL;
    return cowl_datatype_def_axiom_alloc(dt, range, annot);
}

CowlDatatypeDefAxiom* cowl_datatype_def_axiom_retain(CowlDatatypeDefAxiom *axiom) {
    return cowl_object_retain(axiom);
}

void cowl_datatype_def_axiom_release(CowlDatatypeDefAxiom *axiom) {
    if (axiom && !cowl_object_release(axiom)) {
        cowl_datatype_def_axiom_free(axiom);
    }
}

CowlDatatype* cowl_datatype_def_axiom_get_datatype(CowlDatatypeDefAxiom *axiom) {
    return axiom->datatype;
}

CowlDataRange* cowl_datatype_def_axiom_get_range(CowlDatatypeDefAxiom *axiom) {
    return axiom->range;
}

CowlAnnotationVec* cowl_datatype_def_axiom_get_annot(CowlDatatypeDefAxiom *axiom) {
    return cowl_axiom_get_annot(axiom);
}

CowlString* cowl_datatype_def_axiom_to_string(CowlDatatypeDefAxiom *axiom)
    COWL_TO_STRING_IMPL(datatype_def_axiom, axiom)

bool cowl_datatype_def_axiom_equals(CowlDatatypeDefAxiom *lhs, CowlDatatypeDefAxiom *rhs) {
    return cowl_axiom_equals_impl(lhs, rhs,
                                  cowl_datatype_equals(lhs->datatype, rhs->datatype) &&
                                  cowl_data_range_equals(lhs->range, rhs->range));
}

cowl_uint_t cowl_datatype_def_axiom_hash(CowlDatatypeDefAxiom *axiom) {
    return cowl_object_hash_get(axiom);
}

bool cowl_datatype_def_axiom_iterate_primitives(CowlDatatypeDefAxiom *axiom, CowlIterator *iter,
                                                CowlPrimitiveFlags flags) {
    return (cowl_datatype_iterate_primitives(axiom->datatype, iter, flags) &&
            cowl_data_range_iterate_primitives(axiom->range, iter, flags) &&
            cowl_axiom_annot_iterate_primitives(axiom, iter, flags));
}
