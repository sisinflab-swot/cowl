/// @author Ivano Bilenchi

#ifndef COWL_ITERATOR_H
#define COWL_ITERATOR_H

#include "cowl_std.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlOntology);

typedef bool (*CowlAxiomIterator)(void *ctx, CowlAxiom *axiom);
typedef bool (*CowlClsExpIterator)(void *ctx, CowlClsExp *exp);
typedef bool (*CowlDataPropExpIterator)(void *ctx, CowlDataPropExp *prop);
typedef bool (*CowlObjPropExpIterator)(void *ctx, CowlObjPropExp *prop);
typedef bool (*CowlIndividualIterator)(void *ctx, CowlIndividual *ind);
typedef bool (*CowlEntityIterator)(void *ctx, CowlEntity entity);
typedef bool (*CowlOntologyIterator)(void *ctx, CowlOntology *ontology);

typedef bool (*CowlAnnotPropIterator)(void *ctx, CowlAnnotProp *prop);
typedef bool (*CowlClassIterator)(void *ctx, CowlClass *cls);
typedef bool (*CowlDataPropIterator)(void *ctx, CowlDataProp *prop);
typedef bool (*CowlDatatypeIterator)(void *ctx, CowlDatatype *datatype);
typedef bool (*CowlObjPropIterator)(void *ctx, CowlObjProp *prop);
typedef bool (*CowlNamedIndIterator)(void *ctx, CowlNamedInd *ind);
typedef bool (*CowlAnonIndIterator)(void *ctx, CowlAnonInd *ind);
typedef bool (*CowlAnnotationIterator)(void *ctx, CowlAnnotation *annotation);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
