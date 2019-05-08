/// @author Ivano Bilenchi

#ifndef COWL_PARSER_PRIVATE_H
#define COWL_PARSER_PRIVATE_H

#include "cowl_parser.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlOntologyId);

cowl_struct_decl_mutable(CowlOntology, CowlMutableOntology);

UHASH_MAP_DECL(CowlPrefixNsMap, CowlString*, CowlString*)

cowl_struct(CowlParser) {
    UHash(CowlPrefixNsMap) *prefix_ns_map;
    CowlMutableOntology *ontology;
    Vector(CowlError) *errors;
};

void cowl_parser_set_id(CowlParser *parser, CowlOntologyId *id);
void cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom);

void cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns);
CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, char const *cstring, cowl_uint_t length);

void cowl_parser_log_error(CowlParser *parser, CowlErrorCode code,
                           char const *description, cowl_uint_t line);

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
