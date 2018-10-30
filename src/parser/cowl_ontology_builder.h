/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_BUILDER_H
#define COWL_ONTOLOGY_BUILDER_H

#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlIRI const CowlIRI;
typedef struct CowlString const CowlString;
typedef struct CowlOntology const CowlOntology;
typedef struct CowlOntology CowlMutableOntology;
typedef struct CowlOntologyId const CowlOntologyId;

KHASH_MAP_UTILS_DECL(CowlPrefixNsMap, CowlString*, CowlString*);

typedef struct CowlOntoBuilder {
    khash_t(CowlPrefixNsMap) *prefix_ns_map;
    CowlMutableOntology *ontology;
} CowlOntoBuilder;

CowlOntoBuilder* cowl_onto_builder_alloc(void);
void cowl_onto_builder_free(CowlOntoBuilder *builder);

CowlOntology* cowl_onto_builder_build(CowlOntoBuilder *builder);

void cowl_onto_builder_set_id(CowlOntoBuilder *builder, CowlOntologyId *id);
void cowl_onto_builder_add_axiom(CowlOntoBuilder *builder, CowlAxiom *axiom);

void cowl_onto_builder_register_ns(CowlOntoBuilder *builder, CowlString *prefix, CowlString *ns);
CowlIRI* cowl_onto_builder_get_full_iri(CowlOntoBuilder *builder,
                                        char const *cstring, uint32_t length);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_BUILDER_H
