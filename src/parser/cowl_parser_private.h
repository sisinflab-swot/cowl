/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_PRIVATE_H
#define COWL_PARSER_PRIVATE_H

#include "cowl_parser.h"
#include "cowl_node_id.h"
#include "cowl_object_private.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlOntologyID);

typedef uvec_struct(CowlObjectPtr) UVec(CowlObjectPtr);
typedef uhash_struct(CowlObjectTable) UHash(CowlObjectTable);

UHASH_DECL(CowlNodeIdMap, CowlString*, CowlNodeID)

cowl_struct(CowlParser) {
    CowlObject super;
    UHash(CowlObjectTable) *prefix_ns_map;
    UHash(CowlNodeIdMap) *node_id_map;
    CowlOntology *ontology;
    CowlString *source;
    void *scanner;
    CowlErrorHandler handler;
    CowlImportLoader loader;
};

cowl_ret cowl_parser_load_import(CowlParser *parser, CowlIRI *iri, CowlOntology **import);
CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, CowlRawString string);
CowlNodeID cowl_parser_get_node_id(CowlParser *parser, CowlRawString id);

void cowl_parser_set_id(CowlParser *parser, CowlOntologyID id);
cowl_ret cowl_parser_set_imports(CowlParser *parser, UVec(CowlObjectPtr) *imports);
cowl_ret cowl_parser_set_annotations(CowlParser *parser, UVec(CowlObjectPtr) *annot);
cowl_ret cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom);
cowl_ret cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns);

void cowl_parser_handle_error(CowlParser *parser, cowl_ret code, char const *description);
void cowl_parser_handle_error_type(CowlParser *parser, cowl_ret code);

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
