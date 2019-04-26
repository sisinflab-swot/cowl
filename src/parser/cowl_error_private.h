/// @author Ivano Bilenchi

#ifndef COWL_ERROR_PRIVATE_H
#define COWL_ERROR_PRIVATE_H

#include "cowl_error.h"

COWL_BEGIN_DECLS

#define cowl_error_init(CODE, STR, LINE) {                                                          \
    .code = (CODE),                                                                                 \
    .description = cowl_string_get((STR), (cowl_uint_t)strlen(STR), false),                         \
    .line = (LINE)                                                                                  \
}

#define cowl_error_deinit(ERR) cowl_string_release((ERR).description)

COWL_END_DECLS

#endif // COWL_ERROR_PRIVATE_H
