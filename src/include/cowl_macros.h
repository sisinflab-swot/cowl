/// @author Ivano Bilenchi

#ifndef COWL_MACROS_H
#define COWL_MACROS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

#define cowl_array_size(ARRAY) (sizeof(ARRAY) / sizeof(*(ARRAY)))

COWL_END_DECLS

#endif // COWL_MACROS_H
