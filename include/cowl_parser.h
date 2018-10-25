/// @author Ivano Bilenchi

#ifndef COWL_PARSER_H
#define COWL_PARSER_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlOntology const CowlOntology;

CowlOntology* cowl_parse_ontology(char const *path);

COWL_END_DECLS

#endif // COWL_PARSER_H
