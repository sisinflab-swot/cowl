/// @author Ivano Bilenchi

#include "cowl_datatype_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri_private.h"
#include "khash_utils.h"

#pragma mark - Instance map

KHASH_MAP_UTILS_INIT(CowlDatatypeMap, CowlIRI*, CowlDatatype*, cowl_iri_hash, cowl_iri_equals);
static khash_t(CowlDatatypeMap) *inst_map = NULL;

#pragma mark - Private

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

#pragma mark - Public

CowlDatatype* cowl_datatype_get(CowlIRI *iri) {
    if (!inst_map) inst_map = kh_init(CowlDatatypeMap);

    CowlDatatype *datatype;
    bool absent;
    khint_t idx = kh_put_key(CowlDatatypeMap, inst_map, iri, &absent);

    if (absent) {
        datatype = cowl_datatype_alloc(iri);
        kh_value(inst_map, idx) = datatype;
    } else {
        datatype = kh_value(inst_map, idx);
        cowl_datatype_ref_incr(datatype);
    }

    return datatype;
}

CowlDatatype* cowl_datatype_retain(CowlDatatype *datatype) {
    return cowl_datatype_ref_incr(datatype);
}

void cowl_datatype_release(CowlDatatype *datatype) {
    if (datatype && !cowl_datatype_ref_decr(datatype)) {
        kh_del_val(CowlDatatypeMap, inst_map, datatype->iri);
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
    return kh_ptr_hash_func(datatype);
}

bool cowl_datatype_iterate_signature(CowlDatatype *datatype, void *ctx, CowlEntityIterator iter) {
    return iter(ctx, cowl_entity_wrap_datatype(datatype));
}
