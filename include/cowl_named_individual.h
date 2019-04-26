/// @author Ivano Bilenchi

#ifndef COWL_NAMED_INDIVIDUAL_H
#define COWL_NAMED_INDIVIDUAL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI const CowlIRI;

typedef struct CowlNamedIndividual const CowlNamedIndividual;

CowlNamedIndividual* cowl_named_individual_get(CowlIRI *iri);
CowlNamedIndividual* cowl_named_individual_retain(CowlNamedIndividual *ind);
void cowl_named_individual_release(CowlNamedIndividual *ind);

CowlIRI* cowl_named_individual_get_iri(CowlNamedIndividual *ind);

bool cowl_named_individual_equals(CowlNamedIndividual *lhs, CowlNamedIndividual *rhs);
cowl_uint_t cowl_named_individual_hash(CowlNamedIndividual *ind);

bool cowl_named_individual_iterate_signature(CowlNamedIndividual *ind,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NAMED_INDIVIDUAL_H
