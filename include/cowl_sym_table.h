/**
 * Declares CowlSymTable and its API.
 * 
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_SYM_TABLE_H
#define COWL_SYM_TABLE_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlSymTable);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlTable);
/// @endcond

/**
 * Maps symbols to OWL constructs.
 *
 * @struct CowlSymTable
 */

/**
 * Gets the map that associates prefixes to namespaces.
 *
 * @param st The symbol table.
 * @param reverse If true, the reversed map (namespaces to prefixes) is returned.
 * @return Prefix to namespace map, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlTable* cowl_sym_table_get_prefix_ns_map(CowlSymTable *st, bool reverse);

/**
 * Returns the namespace associated with the specified prefix.
 *
 * @param st The symbol table.
 * @param prefix The prefix.
 * @return Namespace associated with the prefix, or NULL if the prefix cannot be found.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlString* cowl_sym_table_get_ns(CowlSymTable *st, CowlString *prefix);

/**
 * Returns the prefix associated with the specified namespace.
 *
 * @param st The symbol table.
 * @param ns The namespace.
 * @return Prefix associated with the namespace, or NULL if the prefix cannot be found.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlString* cowl_sym_table_get_prefix(CowlSymTable *st, CowlString *ns);

/**
 * Registers the specified prefix-namespace mapping.
 * 
 * @param st The symbol table. 
 * @param prefix The prefix.
 * @param ns The namespace.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
cowl_ret cowl_sym_table_register_prefix(CowlSymTable *st, CowlString *prefix, CowlString *ns);

/**
 * Retrieves the full IRI associated with the specified short IRI.
 *
 * @param st The symbol table.
 * @param ns The short namespace.
 * @param rem The remainder.
 * @return IRI instance, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlIRI* cowl_sym_table_get_full_iri(CowlSymTable *st, UString ns, UString rem);

/**
 * Retrieves the full IRI associated with the specified short IRI.
 *
 * @param st The symbol table.
 * @param short_iri The short IRI.
 * @return IRI instance, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlIRI* cowl_sym_table_parse_full_iri(CowlSymTable *st, UString short_iri);

/**
 * Gets the map that associates import IRIs to ontologies.
 *
 * @param st The symbol table.
 * @param reverse If true, the reversed map (ontologies to IRIs) is returned.
 * @return Import IRI to ontology map, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlTable* cowl_sym_table_get_iri_onto_map(CowlSymTable *st, bool reverse);

/**
 * Gets the import IRI for the specified ontology.
 *
 * @param st The symbol table.
 * @param ontology The ontology.
 * @return Import IRI, or NULL if the ontology has no associated import IRI.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlIRI* cowl_sym_table_get_import_iri(CowlSymTable *st, CowlOntology *ontology);

/**
 * Gets the ontology associated with the specified import IRI.
 *
 * @param st The symbol table.
 * @param iri The import IRI.
 * @return Ontology associated with the import IRI, or NULL if the IRI has no associated ontology.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlOntology* cowl_sym_table_get_onto_for_iri(CowlSymTable *st, CowlIRI *iri);

/**
 * Gets the map that associates local names to anonymous individuals.
 *
 * @param st The symbol table.
 * @param reverse If true, the reversed map (anonymous individuals to local names) is returned.
 * @return Local name to anonymous individual map, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlTable* cowl_sym_table_get_name_anon_map(CowlSymTable *st, bool reverse);

/**
 * Returns the anonymous individual associated with the specified identifier.
 *
 * @param st The symbol table.
 * @param id The identifier.
 * @return Anonymous individual instance, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlAnonInd* cowl_sym_table_get_anon(CowlSymTable *st, UString id);

/**
 * Returns the identifier associated with the specified anonymous individual.
 *
 * @param st The symbol table.
 * @param ind The anonymous individual.
 * @return Identifier, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_PUBLIC
CowlString* cowl_sym_table_get_name_for_anon(CowlSymTable *st, CowlAnonInd *ind);

COWL_END_DECLS

#endif // COWL_SYM_TABLE_H
