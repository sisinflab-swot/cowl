/// @author Ivano Bilenchi

#include "cowl_data_prop_exp_private.h"
#include "cowl_data_prop_private.h"

CowlDataPropExp* cowl_data_prop_exp_retain(CowlDataPropExp *prop) {
    return cowl_object_retain(prop);
}

void cowl_data_prop_exp_release(CowlDataPropExp *prop) {
    cowl_data_prop_release((CowlDataProp *)prop);
}

CowlDataProp* cowl_data_prop_exp_get_prop(CowlDataPropExp *exp) {
    return (CowlDataProp *)exp;
}

bool cowl_data_prop_exp_equals(CowlDataPropExp *lhs, CowlDataPropExp *rhs) {
    return cowl_data_prop_equals((CowlDataProp *)lhs, (CowlDataProp *)rhs);
}

cowl_uint_t cowl_data_prop_exp_hash(CowlDataPropExp *exp) {
    return cowl_data_prop_hash((CowlDataProp *)exp);
}

bool cowl_data_prop_exp_iterate_signature(CowlDataPropExp *prop, CowlEntityIterator *iter) {
    return cowl_data_prop_iterate_signature((CowlDataProp *)prop, iter);
}
