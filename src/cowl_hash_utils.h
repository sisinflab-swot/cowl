/// @author Ivano Bilenchi

#ifndef COWL_HASH_UTILS_H
#define COWL_HASH_UTILS_H

#include "cowl_std.h"

#define COWL_HASH_MULT 31

#define COWL_HASH_INIT_IRI 3
#define COWL_HASH_INIT_ENTITY 5

#define COWL_HASH_INIT_CLASS 7
#define COWL_HASH_INIT_OBJ_COMPL 11
#define COWL_HASH_INIT_OBJ_INTERSECTION 13
#define COWL_HASH_INIT_OBJ_UNION 17
#define COWL_HASH_INIT_OBJ_SOME 19
#define COWL_HASH_INIT_OBJ_ALL 23
#define COWL_HASH_INIT_OBJ_MIN_CARD 29
#define COWL_HASH_INIT_OBJ_MAX_CARD 37
#define COWL_HASH_INIT_OBJ_EXACT_CARD 41

#define COWL_HASH_INIT_OBJ_PROP_EXPR 127
#define COWL_HASH_INIT_OBJ_PROP 131

#define COWL_HASH_INIT_SUBCLASS_AXIOM 179
#define COWL_HASH_INIT_EQ_CLS_AXIOM 181
#define COWL_HASH_INIT_DISJ_CLS_AXIOM 191

#define cowl_hash_iter(hash_acc, hash_new) ((hash_acc) * COWL_HASH_MULT + (hash_new))

#define cowl_hash_1(init, a) (cowl_hash_iter(init, a))
#define cowl_hash_2(init, a, b) (cowl_hash_iter(cowl_hash_iter(init, a), b))
#define cowl_hash_3(init, a, b, c) (cowl_hash_iter(cowl_hash_iter(cowl_hash_iter(init, a), b), c))

#endif // COWL_HASH_UTILS_H
