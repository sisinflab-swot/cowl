/**
 * Declares CowlSymTable and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
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
cowl_struct_decl(CowlIRI);
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
COWL_API
CowlTable *cowl_sym_table_get_prefix_ns_map(CowlSymTable *st, bool reverse);

/**
 * Returns the namespace associated with the specified prefix.
 *
 * @param st The symbol table.
 * @param prefix The prefix.
 * @return Namespace associated with the prefix, or NULL if the prefix cannot be found.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
CowlString *cowl_sym_table_get_ns(CowlSymTable *st, CowlString *prefix);

/**
 * Returns the prefix associated with the specified namespace.
 *
 * @param st The symbol table.
 * @param ns The namespace.
 * @return Prefix associated with the namespace, or NULL if the prefix cannot be found.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
CowlString *cowl_sym_table_get_prefix(CowlSymTable *st, CowlString *ns);

/**
 * Registers the specified prefix-namespace mapping.
 *
 * @param st The symbol table.
 * @param prefix The prefix.
 * @param ns The namespace.
 * @param overwrite If true, the new mapping overwrites the previous one.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
cowl_ret cowl_sym_table_register_prefix(CowlSymTable *st, CowlString *prefix, CowlString *ns,
                                        bool overwrite);

/**
 * Registers the specified prefix-namespace mapping.
 *
 * @param st The symbol table.
 * @param prefix The prefix.
 * @param ns The namespace.
 * @param overwrite If true, the new mapping overwrites the previous one.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
cowl_ret
cowl_sym_table_register_prefix_raw(CowlSymTable *st, UString prefix, UString ns, bool overwrite);

/**
 * Unregisters the specified prefix.
 *
 * @param st The symbol table.
 * @param prefix The prefix.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
cowl_ret cowl_sym_table_unregister_prefix(CowlSymTable *st, CowlString *prefix);

/**
 * Unregisters the specified namespace.
 *
 * @param st The symbol table.
 * @param ns The namespace.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
cowl_ret cowl_sym_table_unregister_ns(CowlSymTable *st, CowlString *ns);

/**
 * Merges the contents of a symbol table in the current one.
 *
 * @param dst The destination symbol table.
 * @param src The source symbol table.
 * @param overwrite If true, conflicting prefixes are overwritten in the destination.
 * @return Return code.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
cowl_ret cowl_sym_table_merge(CowlSymTable *dst, CowlSymTable *src, bool overwrite);

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
COWL_API
CowlIRI *cowl_sym_table_get_full_iri(CowlSymTable *st, UString ns, UString rem);

/**
 * Retrieves the full IRI associated with the specified short IRI.
 *
 * @param st The symbol table.
 * @param short_iri The short IRI.
 * @return IRI instance, or NULL on error.
 *
 * @public @memberof CowlSymTable
 */
COWL_API
CowlIRI *cowl_sym_table_parse_full_iri(CowlSymTable *st, UString short_iri);

COWL_END_DECLS

#endif // COWL_SYM_TABLE_H
