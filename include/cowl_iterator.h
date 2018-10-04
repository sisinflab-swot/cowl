/// @author Ivano Bilenchi

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_std.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom CowlAxiom;
typedef struct CowlClsExp CowlClsExp;

typedef bool (*CowlAxiomIterator)(void *ctx, CowlAxiom const *axiom);
typedef bool (*CowlClsExpIterator)(void *ctx, CowlClsExp const *exp);
typedef bool (*CowlEntityIterator)(void *ctx, CowlEntity entity);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
