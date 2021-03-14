/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#undef UHASH_MALLOC
#undef UHASH_REALLOC
#undef UHASH_FREE

#define UHASH_MALLOC malloc
#define UHASH_REALLOC realloc
#define UHASH_FREE free

#include "cowl_api.h"
#include "cowl_object_private.h"

typedef void* CowlAllocPtr;
UHASH_INIT(CowlAllocTable, CowlAllocPtr, UHASH_VAL_IGNORE, uhash_ptr_hash, uhash_identical)

static UHash(CowlAllocTable) *alloc_table;

void cowl_leak_debug_init(void) {
    alloc_table = uhset_alloc(CowlAllocTable);
}

void cowl_leak_debug_deinit(void) {
    uhash_free(CowlAllocTable, alloc_table);
}

cowl_uint cowl_leak_debug_count(void) {
    uhash_resize(CowlAllocTable, alloc_table, uhash_count(alloc_table));
    return uhash_count(alloc_table);
}

void cowl_leak_debug_print(void) {
    unsigned i = 0;
    CowlLogger *logger = cowl_logger_console_get();

    uhash_foreach_key(CowlAllocTable, alloc_table, obj, {
        if (!obj || obj == logger) continue;
        cowl_logger_logf(logger, "Leak %u: ", ++i);
        cowl_logger_consume(logger, cowl_object_to_debug_string(obj));
        cowl_logger_logs(logger, "\n");
    });

    cowl_logger_release(logger);
}

void* cowl_custom_malloc(size_t size) {
    void *ptr = malloc(size);
    uhset_insert(CowlAllocTable, alloc_table, ptr);
    return ptr;
}

void* cowl_custom_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);

    if (ptr != new_ptr) {
        uhset_remove(CowlAllocTable, alloc_table, ptr);
        uhset_insert(CowlAllocTable, alloc_table, new_ptr);
    }

    return new_ptr;
}

void cowl_custom_free(void *ptr) {
    uhset_remove(CowlAllocTable, alloc_table, ptr);
    free(ptr);
}
