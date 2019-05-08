/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_H
#define COWL_DATA_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlDataProp);

CowlDataProp* cowl_data_prop_get(CowlIRI *iri);
CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop);
void cowl_data_prop_release(CowlDataProp *prop);

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop);

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs);
cowl_uint_t cowl_data_prop_hash(CowlDataProp *prop);

bool cowl_data_prop_iterate_signature(CowlDataProp *prop, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_H
