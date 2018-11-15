/// @author Ivano Bilenchi

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_std.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlIndividual const CowlIndividual;
typedef struct CowlObjPropExp const CowlObjPropExp;
typedef struct CowlAnonIndividual const CowlAnonIndividual;

typedef bool (*CowlAxiomIterator)(void *ctx, CowlAxiom *axiom);
typedef bool (*CowlClsExpIterator)(void *ctx, CowlClsExp *exp);
typedef bool (*CowlObjPropExpIterator)(void *ctx, CowlObjPropExp *prop);
typedef bool (*CowlIndividualIterator)(void *ctx, CowlIndividual *ind);
typedef bool (*CowlEntityIterator)(void *ctx, CowlEntity entity);

typedef bool (*CowlClassIterator)(void *ctx, CowlClass *cls);
typedef bool (*CowlObjPropIterator)(void *ctx, CowlObjProp *prop);
typedef bool (*CowlNamedIndividualIterator)(void *ctx, CowlNamedIndividual *ind);
typedef bool (*CowlAnonIndividualIterator)(void *ctx, CowlAnonIndividual *ind);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
