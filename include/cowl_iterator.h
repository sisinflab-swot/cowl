/// @author Ivano Bilenchi

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_std.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlAnonIndividual);

typedef bool (*CowlAxiomIterator)(void *ctx, CowlAxiom *axiom);
typedef bool (*CowlClsExpIterator)(void *ctx, CowlClsExp *exp);
typedef bool (*CowlDataPropExpIterator)(void *ctx, CowlDataPropExp *prop);
typedef bool (*CowlObjPropExpIterator)(void *ctx, CowlObjPropExp *prop);
typedef bool (*CowlIndividualIterator)(void *ctx, CowlIndividual *ind);
typedef bool (*CowlEntityIterator)(void *ctx, CowlEntity entity);

typedef bool (*CowlClassIterator)(void *ctx, CowlClass *cls);
typedef bool (*CowlDataPropIterator)(void *ctx, CowlDataProp *prop);
typedef bool (*CowlDatatypeIterator)(void *ctx, CowlDatatype *datatype);
typedef bool (*CowlObjPropIterator)(void *ctx, CowlObjProp *prop);
typedef bool (*CowlNamedIndividualIterator)(void *ctx, CowlNamedIndividual *ind);
typedef bool (*CowlAnonIndividualIterator)(void *ctx, CowlAnonIndividual *ind);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
