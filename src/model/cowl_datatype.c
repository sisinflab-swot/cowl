/// @author Ivano Bilenchi

#include "cowl_datatype_private.h"
#include "cowl_iri_private.h"
#include "uhash.h"

UHASH_MAP_INIT(CowlDatatypeMap, CowlIRI*, CowlDatatype*, cowl_iri_hash, cowl_iri_equals)
static UHash(CowlDatatypeMap) *inst_map = NULL;

static CowlDatatype* cowl_datatype_alloc(CowlIRI *iri) {
    CowlDatatype init = COWL_DATATYPE_INIT(cowl_iri_retain(iri));
    struct CowlDatatype *datatype = malloc(sizeof(*datatype));
    memcpy(datatype, &init, sizeof(*datatype));
    return datatype;
}

static void cowl_datatype_free(CowlDatatype *datatype) {
    if (!datatype) return;
    cowl_iri_release(datatype->iri);
    free((void *)datatype);
}

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    if (!inst_map) inst_map = uhash_alloc(CowlDatatypeMap);

    CowlDatatype *datatype;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlDatatypeMap, inst_map, iri, &ret);

    if (ret == UHASH_INSERTED) {
        datatype = cowl_datatype_alloc(iri);
        uhash_value(inst_map, idx) = datatype;
    } else {
        datatype = uhash_value(inst_map, idx);
        cowl_datatype_ref_incr(datatype);
    }

    return datatype;
}

CowlDatatype* cowl_datatype_retain(CowlDatatype *datatype) {
    return cowl_datatype_ref_incr(datatype);
}

void cowl_datatype_release(CowlDatatype *datatype) {
    if (datatype && !cowl_datatype_ref_decr(datatype)) {
        uhmap_remove(CowlDatatypeMap, inst_map, datatype->iri);
        cowl_datatype_free(datatype);
    }
}

CowlIRI* cowl_datatype_get_iri(CowlDatatype *datatype) {
    return datatype->iri;
}

bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs) {
    return lhs == rhs;
}

uint32_t cowl_datatype_hash(CowlDatatype *datatype) {
    return uhash_ptr_hash(datatype);
}

bool cowl_datatype_iterate_signature(CowlDatatype *datatype, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_datatype(datatype));
}
