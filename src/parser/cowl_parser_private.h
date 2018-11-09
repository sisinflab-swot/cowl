/// @author Ivano Bilenchi

#ifndef COWL_PARSER_PRIVATE_H
#define COWL_PARSER_PRIVATE_H

#include "cowl_parser.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlIRI const CowlIRI;
typedef struct CowlString const CowlString;
typedef struct CowlOntology const CowlOntology;
typedef struct CowlOntology CowlMutableOntology;
typedef struct CowlOntologyId const CowlOntologyId;

KHASH_MAP_UTILS_DECL(CowlPrefixNsMap, CowlString*, CowlString*);

struct CowlParser {
    khash_t(CowlPrefixNsMap) *prefix_ns_map;
    CowlMutableOntology *ontology;
    Vector(CowlError) *errors;
};

void cowl_parser_set_id(CowlParser *parser, CowlOntologyId *id);
void cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom);

void cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns);
CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, char const *cstring, uint32_t length);

void cowl_parser_log_error(CowlParser *parser, CowlErrorCode code,
                           char const *description, uint32_t line);

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
