/// @author Ivano Bilenchi

#include "cowl_api.h"
#include "cowl_vocabulary_private.h"

static bool cowl_api_initialized = false;

void cowl_api_init(void) {
    if (cowl_api_initialized) return;
    cowl_api_initialized = true;
    cowl_vocabulary_init();
}

void cowl_api_deinit(void) {
    if (!cowl_api_initialized) return;
    cowl_vocabulary_deinit();
    cowl_api_initialized = false;
}
