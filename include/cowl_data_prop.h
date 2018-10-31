/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_H
#define COWL_DATA_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI const CowlIRI;

typedef struct CowlDataProp const CowlDataProp;

CowlDataProp* cowl_data_prop_get(CowlIRI *iri);
CowlDataProp* cowl_data_prop_retain(CowlDataProp *prop);
void cowl_data_prop_release(CowlDataProp *prop);

CowlIRI* cowl_data_prop_get_iri(CowlDataProp *prop);

bool cowl_data_prop_equals(CowlDataProp *lhs, CowlDataProp *rhs);
uint32_t cowl_data_prop_hash(CowlDataProp *prop);

bool cowl_data_prop_iterate_signature(CowlDataProp *prop, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_H
