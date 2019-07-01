/// @author Ivano Bilenchi

#ifndef COWL_PARSER_H
#define COWL_PARSER_H

#include "cowl_error.h"
#include "cowl_imports_loader.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlOntology);

cowl_struct_decl(CowlParser);

CowlParser* cowl_parser_alloc(void);
void cowl_parser_free(CowlParser *parser);

void cowl_parser_set_imports_loader(CowlParser *parser, CowlImportsLoader loader);
CowlOntology* cowl_parser_parse_ontology(CowlParser *parser, char const *path,
                                         Vector(CowlError) *errors);

COWL_END_DECLS

#endif // COWL_PARSER_H
