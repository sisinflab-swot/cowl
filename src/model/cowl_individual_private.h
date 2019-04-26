/// @author Ivano Bilenchi

#ifndef COWL_INDIVIDUAL_PRIVATE_H
#define COWL_INDIVIDUAL_PRIVATE_H

#include "cowl_individual.h"

COWL_BEGIN_DECLS

struct CowlIndividual {
    bool is_named;
    cowl_uint_t ref_count;
};

#define COWL_INDIVIDUAL_INIT(N) { .ref_count = 1, .is_named = ((N)) }

#define cowl_individual_ref_get(i) (((struct CowlIndividual *)(i))->ref_count)
#define cowl_individual_ref_incr(i) (++cowl_individual_ref_get(i), (i))
#define cowl_individual_ref_decr(i) (--cowl_individual_ref_get(i))

COWL_END_DECLS

#endif // COWL_INDIVIDUAL_PRIVATE_H
