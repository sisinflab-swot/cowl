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
#include "cowl_object_private.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlOntology);

typedef uvec_struct(CowlObjectPtr) UVec(CowlObjectPtr);
typedef uhash_struct(CowlObjectTable) UHash(CowlObjectTable);

cowl_struct(CowlParser) {
    CowlObject super;
    UHash(CowlObjectTable) *prefix_ns_map;
    UHash(CowlObjectTable) *anon_ind_map;
    CowlOntology *ontology;
    CowlString *source;
    void *scanner;
    CowlErrorHandler handler;
    CowlImportLoader loader;
};

cowl_ret cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns);
CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, CowlRawString string);
CowlAnonInd* cowl_parser_get_anon_ind(CowlParser *parser, CowlRawString id);

void cowl_parser_set_iri(CowlParser *parser, CowlIRI *iri);
void cowl_parser_set_version(CowlParser *parser, CowlIRI *version);
cowl_ret cowl_parser_add_annot(CowlParser *parser, CowlAnnotation *annot);
cowl_ret cowl_parser_add_import(CowlParser *parser, CowlIRI *iri);
cowl_ret cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom);

void cowl_parser_handle_error(CowlParser *parser, cowl_ret code, char const *description);
void cowl_parser_handle_error_type(CowlParser *parser, cowl_ret code);

COWL_END_DECLS

#endif // COWL_PARSER_PRIVATE_H
