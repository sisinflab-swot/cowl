/// @author Ivano Bilenchi

#ifndef COWL_HASH_UTILS_H
#define COWL_HASH_UTILS_H

#include "cowl_std.h"

#define COWL_HASH_MULT 31

#define COWL_HASH_INIT_IRI 3
#define COWL_HASH_INIT_ENTITY 5
#define COWL_HASH_INIT_CLASS_EXPR 7
#define COWL_HASH_INIT_OBJ_PROP_EXPR 11

#define cowl_hs(hash_acc, hash_new) ((hash_acc) * COWL_HASH_MULT + (hash_new))

#define cowl_hash_1(init, a) (cowl_hs(init, a))
#define cowl_hash_2(init, a, b) (cowl_hs(cowl_hs(init, a), b))
#define cowl_hash_3(init, a, b, c) (cowl_hs(cowl_hs(cowl_hs(init, a), b), c))

#endif // COWL_HASH_UTILS_H
