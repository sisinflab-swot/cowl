/// @author Ivano Bilenchi

#ifndef COWL_HASH_UTILS_H
#define COWL_HASH_UTILS_H

#include "cowl_std.h"

#define COWL_HASH_MULT 31

#define COWL_HASH_INIT_IRI 3
#define COWL_HASH_INIT_ENTITY 5
#define COWL_HASH_INIT_CLASS_EXPR 7
#define COWL_HASH_INIT_OBJ_PROP_EXPR 11
#define COWL_HASH_INIT_SUBCLASS_AXIOM 13
#define COWL_HASH_INIT_EQ_CLS_AXIOM 17
#define COWL_HASH_INIT_DISJ_CLS_AXIOM 19

#define cowl_hash_iter(hash_acc, hash_new) ((hash_acc) * COWL_HASH_MULT + (hash_new))

#define cowl_hash_1(init, a) (cowl_hash_iter(init, a))
#define cowl_hash_2(init, a, b) (cowl_hash_iter(cowl_hash_iter(init, a), b))
#define cowl_hash_3(init, a, b, c) (cowl_hash_iter(cowl_hash_iter(cowl_hash_iter(init, a), b), c))

#endif // COWL_HASH_UTILS_H
