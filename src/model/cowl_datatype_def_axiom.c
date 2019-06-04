/// @author Ivano Bilenchi

#include "cowl_datatype_def_axiom_private.h"
#include "cowl_data_range.h"
#include "cowl_datatype.h"
#include "cowl_hash_utils.h"

static CowlDatatypeDefAxiom* cowl_datatype_def_axiom_alloc(CowlDatatype *datatype,
                                                           CowlDataRange *range) {
    cowl_uint_t hash = cowl_hash_2(COWL_HASH_INIT_DATATYPE_DEF_AXIOM,
                                   cowl_datatype_hash(datatype),
                                   cowl_data_range_hash(range));

    CowlDatatypeDefAxiom init = {
        .super = COWL_AXIOM_INIT(CAT_DATATYPE_DEFINITION, hash),
        .datatype = cowl_datatype_retain(datatype),
        .range = cowl_data_range_retain(range)
    };

    cowl_struct(CowlDatatypeDefAxiom) *axiom = malloc(sizeof(*axiom));
    memcpy(axiom, &init, sizeof(*axiom));
    return axiom;
}

static void cowl_datatype_def_axiom_free(CowlDatatypeDefAxiom *axiom) {
    if (!axiom) return;
    cowl_datatype_release(axiom->datatype);
    cowl_data_range_release(axiom->range);
    free((void *)axiom);
}

CowlDatatypeDefAxiom* cowl_datatype_def_axiom_get(CowlDatatype *datatype, CowlDataRange *range) {
    return cowl_datatype_def_axiom_alloc(datatype, range);
}

CowlDatatypeDefAxiom* cowl_datatype_def_axiom_retain(CowlDatatypeDefAxiom *axiom) {
    return cowl_axiom_ref_incr(axiom);
}

void cowl_datatype_def_axiom_release(CowlDatatypeDefAxiom *axiom) {
    if (axiom && !cowl_axiom_ref_decr(axiom)) {
        cowl_datatype_def_axiom_free(axiom);
    }
}

CowlDatatype* cowl_datatype_def_axiom_get_datatype(CowlDatatypeDefAxiom *axiom) {
    return axiom->datatype;
}

CowlDataRange* cowl_datatype_def_axiom_get_range(CowlDatatypeDefAxiom *axiom) {
    return axiom->range;
}

bool cowl_datatype_def_axiom_equals(CowlDatatypeDefAxiom *lhs, CowlDatatypeDefAxiom *rhs) {
    return cowl_datatype_equals(lhs->datatype, rhs->datatype) &&
           cowl_data_range_equals(lhs->range, rhs->range);
}

cowl_uint_t cowl_datatype_def_axiom_hash(CowlDatatypeDefAxiom *axiom) {
    return cowl_axiom_hash_get(axiom);
}

bool cowl_datatype_def_axiom_iterate_signature(CowlDatatypeDefAxiom *axiom, void *ctx,
                                               CowlEntityIterator iter) {
    if (!cowl_datatype_iterate_signature(axiom->datatype, ctx, iter)) return false;
    if (!cowl_data_range_iterate_signature(axiom->range, ctx, iter)) return false;
    return true;
}
