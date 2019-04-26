/// @author Ivano Bilenchi

#ifndef COWL_TYPES_H
#define COWL_TYPES_H

#include "cowl_std.h"
#include "cowl_axiom_type.h"
#include "cowl_cls_exp_type.h"
#include "cowl_entity.h"
#include "cowl_entity_type.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

typedef struct CowlAnonIndividual const CowlAnonIndividual;
typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlClass const CowlClass;
typedef struct CowlClsAssertAxiom const CowlClsAssertAxiom;
typedef struct CowlClsExp const CowlClsExp;
typedef struct UHash(CowlClsExpSet) const CowlClsExpSet;
typedef struct UHash(CowlClsExpSet) CowlMutableClsExpSet;
typedef struct CowlDataProp const CowlDataProp;
typedef struct CowlDataPropExp const CowlDataPropExp;
typedef struct CowlDatatype const CowlDatatype;
typedef struct CowlDeclAxiom const CowlDeclAxiom;
typedef struct CowlIndividual const CowlIndividual;
typedef struct UHash(CowlIndividualSet) const CowlIndividualSet;
typedef struct UHash(CowlIndividualSet) CowlMutableIndividualSet;
typedef struct CowlInverseObjProp const CowlInverseObjProp;
typedef struct CowlIRI const CowlIRI;
typedef struct CowlLogger CowlLogger;
typedef struct CowlNamedIndividual const CowlNamedIndividual;
typedef struct CowlNAryBool const CowlNAryBool;
typedef struct CowlNAryClsAxiom const CowlNAryClsAxiom;
typedef struct CowlObjCard const CowlObjCard;
typedef struct CowlObjCompl const CowlObjCompl;
typedef struct CowlObjProp const CowlObjProp;
typedef struct CowlObjPropAssertAxiom const CowlObjPropAssertAxiom;
typedef struct CowlObjPropCharAxiom const CowlObjPropCharAxiom;
typedef struct CowlObjPropDomainAxiom const CowlObjPropDomainAxiom;
typedef struct CowlObjPropExp const CowlObjPropExp;
typedef struct UHash(CowlObjPropExpSet) const CowlObjPropExpSet;
typedef struct UHash(CowlObjPropExpSet) CowlMutableObjPropExpSet;
typedef struct CowlObjPropRangeAxiom const CowlObjPropRangeAxiom;
typedef struct CowlObjQuant const CowlObjQuant;
typedef struct CowlOntology const CowlOntology;
typedef struct CowlOntologyId const CowlOntologyId;
typedef struct CowlParser const CowlParser;
typedef struct CowlString const CowlString;
typedef struct CowlSubClsAxiom const CowlSubClsAxiom;

COWL_END_DECLS

#endif // COWL_TYPES_H
