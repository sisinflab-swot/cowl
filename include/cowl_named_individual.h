/// @author Ivano Bilenchi

#ifndef COWL_NAMED_INDIVIDUAL_H
#define COWL_NAMED_INDIVIDUAL_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI CowlIRI;

typedef struct CowlNamedIndividual CowlNamedIndividual;

CowlIRI const* cowl_named_individual_get_iri(CowlNamedIndividual const *ind);

bool cowl_named_individual_equals(CowlNamedIndividual const *lhs, CowlNamedIndividual const *rhs);
uint32_t cowl_named_individual_hash(CowlNamedIndividual const *ind);

bool cowl_named_individual_iterate_signature(CowlNamedIndividual const *ind,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NAMED_INDIVIDUAL_H
