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

#define COWL_ITERATOR_PTR *
#define COWL_ITERATOR_NO_PTR

#define cowl_iterator_def(T, PTR)                                                                   \
    typedef cowl_struct(T##Iterator) {                                                              \
        void *ctx;                                                                                  \
        bool (*for_each)(void *ctx, T PTR elem);                                                    \
    } const T##Iterator

#define cowl_iterator_init(T, CTX, FOR_EACH) \
    ((T##Iterator){ .ctx = (void *)(CTX), .for_each = (FOR_EACH) })

#define cowl_iterate(iter, elem) ((iter)->for_each((iter)->ctx, elem))

cowl_iterator_def(CowlEntity, COWL_ITERATOR_NO_PTR);

cowl_iterator_def(CowlAxiom, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlClsExp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlDataPropExp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlObjPropExp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlIndividual, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlOntology, COWL_ITERATOR_PTR);

cowl_iterator_def(CowlAnnotProp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlClass, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlDataProp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlDatatype, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlObjProp, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlNamedInd, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlAnonInd, COWL_ITERATOR_PTR);
cowl_iterator_def(CowlAnnotation, COWL_ITERATOR_PTR);

COWL_END_DECLS

#endif // COWL_ITERATOR_H
