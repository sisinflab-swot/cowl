/// @author Ivano Bilenchi

#ifndef COWL_PARSER_PRIVATE_H
#define COWL_PARSER_PRIVATE_H

#include "cowl_node_id.h"
#include "cowl_parser.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlOntologyID);

typedef vector_struct(CowlAnnotationPtr) Vector(CowlAnnotationPtr);
typedef vector_struct(CowlOntologyPtr) Vector(CowlOntologyPtr);

UHASH_MAP_DECL(CowlPrefixNsMap, CowlString*, CowlString*)
UHASH_MAP_DECL(CowlNodeIdMap, CowlString*, CowlNodeID)

cowl_struct(CowlParser) {
    UHash(CowlPrefixNsMap) *prefix_ns_map;
    UHash(CowlNodeIdMap) *node_id_map;
    cowl_struct(CowlOntology) *ontology;
    Vector(CowlError) *errors;
    CowlImportsLoader loader;
};

CowlOntology* cowl_parser_load_import(CowlParser *parser, CowlIRI *iri);
CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, char const *cstring, cowl_uint_t length);
CowlNodeID cowl_parser_get_node_id(CowlParser *parser, CowlString *id);

void cowl_parser_set_id(CowlParser *parser, CowlOntologyID *id);
void cowl_parser_set_imports(CowlParser *parser, Vector(CowlOntologyPtr) *imports);
void cowl_parser_set_annotations(CowlParser *parser, Vector(CowlAnnotationPtr) *annot);
void cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom);
void cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns);

void cowl_parser_log_error(CowlParser *parser, CowlErrorCode code,
                           char const *description, cowl_uint_t line);

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
