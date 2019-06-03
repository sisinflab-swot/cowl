/// @author Ivano Bilenchi

#ifndef COWL_NARY_DATA_PROP_AXIOM_H
#define COWL_NARY_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlDataPropExpSet);

cowl_struct_decl(CowlNAryDataPropAxiom);

CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_get(CowlNAryAxiomType type,
                                                     CowlDataPropExpSet *props);
CowlNAryDataPropAxiom* cowl_nary_data_prop_axiom_retain(CowlNAryDataPropAxiom *axiom);
void cowl_nary_data_prop_axiom_release(CowlNAryDataPropAxiom *axiom);

CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom);
CowlDataPropExpSet* cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom);

bool cowl_nary_data_prop_axiom_equals(CowlNAryDataPropAxiom *lhs, CowlNAryDataPropAxiom *rhs);
cowl_uint_t cowl_nary_data_prop_axiom_hash(CowlNAryDataPropAxiom *axiom);

bool cowl_nary_data_prop_axiom_iterate_signature(CowlNAryDataPropAxiom *axiom,
                                                 void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_DATA_PROP_AXIOM_H
