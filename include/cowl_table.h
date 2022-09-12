/**
 * Declares CowlTable and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TABLE_H
#define COWL_TABLE_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
UHASH_DECL_PI_SPEC(CowlObjectTable, void*, void*, COWL_PUBLIC)
cowl_struct_decl(CowlTable);
/// @endcond

/**
 * Hash table of #CowlObject elements.
 *
 * @struct CowlTable
 * @extends CowlObject
 */

/**
 * Returns a retained hash table.
 *
 * @param table Underlying raw hash table.
 * @return Retained hash table, or NULL on error.
 *
 * @note You must not use the raw hash table after passing it to this function.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
CowlTable* cowl_table(UHash(CowlObjectTable) *table);

/**
 * Returns a retained hash table with no elements.
 *
 * @return [CowlTable*] Retained hash table, or NULL on error.
 *
 * @public @related CowlTable
 */
#define cowl_table_empty() cowl_table(NULL)

/**
 * Retains the specified hash table.
 *
 * @param table The hash table.
 * @return Retained hash table.
 *
 * @public @memberof CowlTable
 */
COWL_INLINE
CowlTable* cowl_table_retain(CowlTable *table) {
    return (CowlTable *)cowl_retain(table);
}

/**
 * Releases the specified hash table.
 *
 * @param table The hash table.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
void cowl_table_release(CowlTable *table);

/**
 * Returns the underlying raw hash table.
 *
 * @param table The hash table.
 * @return Underlying raw hash table.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
UHash(CowlObjectTable) const* cowl_table_get_data(CowlTable *table);

/**
 * Returns the string representation of the specified hash table.
 *
 * @param table The hash table.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlVector
 */
COWL_INLINE
CowlString* cowl_table_to_string(CowlTable *table) {
    return cowl_to_string(table);
}

/**
 * Returns the number of elements in the hash table.
 *
 * @param table The hash table.
 * @return Number of elements in The hash table.
 *
 * @public @memberof CowlTable
 */
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
 *
 * @public @memberof CowlTable
 */
COWL_INLINE
void* cowl_table_get_value(CowlTable *table, void *key) {
    return uhmap_get(CowlObjectTable, cowl_table_get_data(table), key, NULL);
}

/**
 * Returns one of the keys in the hash table.
 *
 * @param table The hash table.
 * @return One of the keys in the hash table.
 *
 * @public @memberof CowlTable
 */
COWL_INLINE
void* cowl_table_get_any(CowlTable *table) {
    return uhset_get_any(CowlObjectTable, cowl_table_get_data(table), NULL);
}

/**
 * Checks whether the hash table contains the specified key.
 *
 * @param table The hash table.
 * @param key The key.
 * @return True if the object is contained in the hash table, false otherwise.
 *
 * @public @memberof CowlTable
 */
COWL_INLINE
bool cowl_table_contains(CowlTable *table, void *key) {
    return uhash_contains(CowlObjectTable, cowl_table_get_data(table), key);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
bool cowl_table_equals(CowlTable *lhs, CowlTable *rhs);

/**
 * Hash function.
 *
 * @param table The hash table.
 * @return The hash value.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
ulib_uint cowl_table_hash(CowlTable *table);

/**
 * Iterates over the primitives referenced by the specified hash table.
 *
 * @param table The hash table.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlTable
 */
COWL_PUBLIC
bool cowl_table_iterate_primitives(CowlTable *table, CowlPrimitiveFlags flags, CowlIterator *iter);

/**
 * Iterates over the entries in the hash table.
 *
 * @param table [CowlTable *] The hash table.
 * @param obj [symbol] Name of the variable holding the current index, key and value.
 *
 * @public @related CowlTable
 */
#define cowl_table_foreach(table, obj) \
    uhash_foreach(CowlObjectTable, cowl_table_get_data(table), obj)

COWL_END_DECLS

#endif // COWL_TABLE_H
