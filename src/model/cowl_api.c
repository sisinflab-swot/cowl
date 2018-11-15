/// @author Ivano Bilenchi

#include "cowl_api.h"
#include "cowl_vocabulary_private.h"

void cowl_api_init(void) {
    static bool api_initialized = false;

    if (!api_initialized) {
        api_initialized = true;
        cowl_vocabulary_init();
    }
}
