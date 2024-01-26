/**
 * Declares CowlTable and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TABLE_H
#define COWL_TABLE_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/**
 * @func{#UHash(T)} of @type{#CowlObject *} elements.
 *
 * @alias typedef UHash(CowlObjectTable) UHash(CowlObjectTable);
 */

/// @cond
UHASH_DECL_PI_SPEC(CowlObjectTable, CowlAny *, CowlAny *, COWL_API)
/// @endcond

/**
 * Hash table of @type{#CowlObject} elements.
 *
 * @superstruct{CowlObject}
 * @struct CowlTable
 */
cowl_struct_decl(CowlTable);

/**
 * @defgroup CowlTable CowlTable API
 * @{
 */

/**
 * Returns an hash table.
 *
 * @param table Underlying raw hash table.
 * @return Hash table, or NULL on error.
 *
 * @note You must not use the raw hash table after passing it to this function.
 * @note Keys and values in the raw table are retained by this constructor.
 */
COWL_API
COWL_RETAINED
CowlTable *cowl_table(UHash(CowlObjectTable) *table);

/**
 * Returns an hash table with no elements.
 *
 * @return Hash table, or NULL on error.
 * @alias CowlTable *cowl_table_empty(void);
 */
COWL_RETAINED
#define cowl_table_empty() cowl_table(NULL)

/**
 * Returns the underlying raw hash table.
 *
 * @param table The hash table.
 * @return Underlying raw hash table.
 */
COWL_API
COWL_PURE
UHash(CowlObjectTable) const *cowl_table_get_data(CowlTable *table);

/**
 * Returns the number of elements in the hash table.
 *
 * @param table The hash table.
 * @return Number of elements in The hash table.
 */
COWL_PURE
COWL_INLINE
ulib_uint cowl_table_count(CowlTable *table) {
    return uhash_count(CowlObjectTable, cowl_table_get_data(table));
}

/**
 * Returns the value associated with the specified key.
 *
 * @param table The hash table.
 * @param key The key.
 * @return Value associated with the key, or NULL if the key is not present.
 */
COWL_PURE
COWL_INLINE
CowlAny *cowl_table_get_value(CowlTable *table, CowlAny *key) {
    return uhmap_get(CowlObjectTable, cowl_table_get_data(table), key, NULL);
}

/**
 * Returns one of the keys in the hash table.
 *
 * @param table The hash table.
 * @return One of the keys in the hash table.
 */
COWL_PURE
COWL_INLINE
CowlAny *cowl_table_get_any(CowlTable *table) {
    return uhset_get_any(CowlObjectTable, cowl_table_get_data(table), NULL);
}

/**
 * Checks whether the hash table contains the specified key.
 *
 * @param table The hash table.
 * @param key The key.
 * @return True if the object is contained in the hash table, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_table_contains(CowlTable *table, CowlAny *key) {
    return uhash_contains(CowlObjectTable, cowl_table_get_data(table), key);
}

/**
 * Iterates over the entries in the hash table.
 *
 * @param table @type{#CowlTable *} The hash table.
 * @param obj @type{symbol} Name of the variable holding the current index, key and value.
 */
#define cowl_table_foreach(table, obj)                                                             \
    uhash_foreach (CowlObjectTable, cowl_table_get_data(table), obj)

/// @}

COWL_END_DECLS

#endif // COWL_TABLE_H
