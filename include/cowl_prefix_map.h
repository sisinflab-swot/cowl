/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PREFIX_MAP_H
#define COWL_PREFIX_MAP_H

#include "cowl_attrs.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlTable);
/// @endcond

/**
 * Holds the mapping between prefixes and namespaces.
 *
 * @superstruct{CowlObject}
 * @struct CowlPrefixMap
 */
cowl_struct_decl(CowlPrefixMap);

/**
 * @defgroup CowlPrefixMap CowlPrefixMap API
 * @{
 */

/**
 * Creates a new prefix map.
 *
 * @return Prefix map, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlPrefixMap *cowl_prefix_map(void);

/**
 * Gets the table that associates prefixes to namespaces.
 *
 * @param map The prefix map.
 * @param reverse If true, the reversed map (namespaces to prefixes) is returned.
 * @return Table, or NULL on error.
 */
COWL_API
COWL_PURE
CowlTable *cowl_prefix_map_get_table(CowlPrefixMap *map, bool reverse);

/**
 * Returns the namespace associated with the specified prefix.
 *
 * @param map The prefix map.
 * @param prefix The prefix.
 * @return Namespace associated with the prefix, or NULL if the prefix cannot be found.
 */
COWL_API
COWL_PURE
CowlString *cowl_prefix_map_get_ns(CowlPrefixMap *map, CowlString *prefix);

/**
 * Returns the prefix associated with the specified namespace.
 *
 * @param map The prefix map.
 * @param ns The namespace.
 * @return Prefix associated with the namespace, or NULL if the prefix cannot be found.
 */
COWL_API
COWL_PURE
CowlString *cowl_prefix_map_get_prefix(CowlPrefixMap *map, CowlString *ns);

/**
 * Registers the specified prefix-namespace mapping.
 *
 * @param map The prefix map.
 * @param prefix The prefix.
 * @param ns The namespace.
 * @param overwrite If true, the new mapping overwrites the previous one.
 * @return Return code.
 */
COWL_API
cowl_ret
cowl_prefix_map_add(CowlPrefixMap *map, CowlString *prefix, CowlString *ns, bool overwrite);

/**
 * Registers the specified prefix-namespace mapping.
 *
 * @param map The prefix map.
 * @param prefix The prefix.
 * @param ns The namespace.
 * @param overwrite If true, the new mapping overwrites the previous one.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_prefix_map_add_raw(CowlPrefixMap *map, UString prefix, UString ns, bool overwrite);

/**
 * Unregisters the specified prefix.
 *
 * @param map The prefix map.
 * @param prefix The prefix.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_prefix_map_remove_prefix(CowlPrefixMap *map, CowlString *prefix);

/**
 * Unregisters the specified namespace.
 *
 * @param map The prefix map.
 * @param ns The namespace.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_prefix_map_remove_ns(CowlPrefixMap *map, CowlString *ns);

/**
 * Merges the contents of a prefix map in the current one.
 *
 * @param dst The destination prefix map.
 * @param src The source prefix map.
 * @param overwrite If true, conflicting prefixes are overwritten in the destination.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_prefix_map_merge(CowlPrefixMap *dst, CowlPrefixMap *src, bool overwrite);

/**
 * Retrieves the full IRI associated with the specified short IRI prefix and remainder.
 *
 * @param map The prefix map.
 * @param prefix The prefix.
 * @param rem The remainder.
 * @return IRI instance, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlIRI *cowl_prefix_map_get_iri(CowlPrefixMap *map, UString prefix, UString rem);

/**
 * Parses an IRI from the specified short IRI.
 *
 * @param map The prefix map.
 * @param short_iri The short IRI.
 * @return IRI instance, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlIRI *cowl_prefix_map_parse_short_iri(CowlPrefixMap *map, UString short_iri);

/**
 * Parses an IRI from the specified string, which must be the representation of either
 * a short or a full IRI.
 *
 * @param map The prefix map.
 * @param str The IRI string.
 * @return IRI instance, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlIRI *cowl_prefix_map_parse_iri(CowlPrefixMap *map, UString str);

/// @}

COWL_END_DECLS

#endif // COWL_PREFIX_MAP_H
