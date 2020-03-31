/**
 * Declares the default allocator and allows specifying custom allocators.
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ALLOC_H
#define COWL_ALLOC_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/**
 * Allocates size bytes of uninitialized storage.
 *
 * @param size [size_t] Number of bytes to allocate.
 * @return Pointer to the beginning of the allocated memory, or NULL on failure.
 */
#ifndef cowl_malloc
    #define cowl_malloc(size) malloc(size)
#endif

/**
 * Reallocates the given memory area with a new size.
 *
 * @param ptr [void *] Pointer to the memory area to reallocate.
 * @param size [size_t] New size of the memory area in bytes.
 * @return Pointer to the beginning of the allocated memory, or NULL on failure.
 */
#ifndef cowl_realloc
    #define cowl_realloc(ptr, size) realloc(ptr, size)
#endif

/**
 * Deallocates the given memory area.
 *
 * @param ptr [void *] Pointer to the memory area to deallocate.
 */
#ifndef cowl_free
    #define cowl_free(ptr) free(ptr)
#endif

/**
 * Allocates memory to hold the type of the pointed variable.
 *
 * @param ptr [T*] Typed pointer to the variable.
 * @return [void *] Pointer to the allocated memory area.
 */
#define cowl_alloc(ptr) (cowl_malloc(sizeof(*(ptr))))

COWL_END_DECLS

#endif // COWL_ALLOC_H
