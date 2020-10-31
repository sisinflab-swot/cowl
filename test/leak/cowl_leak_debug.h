/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LEAK_DEBUG_ALLOC_H
#define COWL_LEAK_DEBUG_ALLOC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

void cowl_leak_debug_init(void);
void cowl_leak_debug_deinit(void);

cowl_uint_t cowl_leak_debug_count(void);
void cowl_leak_debug_print(void);

void* cowl_custom_malloc(size_t size);
void* cowl_custom_realloc(void *ptr, size_t size);
void cowl_custom_free(void *ptr);

COWL_END_DECLS

#endif // COWL_LEAK_DEBUG_ALLOC_H
