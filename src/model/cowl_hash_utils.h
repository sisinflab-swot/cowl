/// @author Ivano Bilenchi

#ifndef COWL_HASH_UTILS_H
#define COWL_HASH_UTILS_H

#include "cowl_std.h"

#define COWL_HASH_MULT 31

#define COWL_HASH_INIT_STRING 3
#define COWL_HASH_INIT_IRI 5
#define COWL_HASH_INIT_OBJ_COMPL 7
#define COWL_HASH_INIT_NARY_BOOL 11
#define COWL_HASH_INIT_OBJ_QUANT 13
#define COWL_HASH_INIT_OBJ_CARD 17
#define COWL_HASH_INIT_OBJ_HAS_VALUE 19
#define COWL_HASH_INIT_OBJ_HAS_SELF 23
#define COWL_HASH_INIT_OBJECT_ONE_OF 29

#define COWL_HASH_INIT_LITERAL 37
#define COWL_HASH_INIT_DATA_COMPL 41
#define COWL_HASH_INIT_DATA_ONE_OF 43
#define COWL_HASH_INIT_DATA_NARY 47
#define COWL_HASH_INIT_DATA_QUANT 53
#define COWL_HASH_INIT_DATA_HAS_VALUE 59

#define COWL_HASH_INIT_OBJ_PROP 127
#define COWL_HASH_INIT_INV_OBJ_PROP 131

#define COWL_HASH_INIT_NAMED_INDIVIDUAL 151
#define COWL_HASH_INIT_ANON_INDIVIDUAL 157

#define COWL_HASH_INIT_DECL_AXIOM 179
#define COWL_HASH_INIT_SUBCLASS_AXIOM 181
#define COWL_HASH_INIT_NARY_CLS_AXIOM 191
#define COWL_HASH_INIT_DISJ_UNION_AXIOM 193

#define COWL_HASH_INIT_SUB_OBJ_PROP_AXIOM 197
#define COWL_HASH_INIT_NARY_OBJ_PROP_AXIOM 199
#define COWL_HASH_INIT_INV_OBJ_PROP_AXIOM 211
#define COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM 223
#define COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM 227
#define COWL_HASH_INIT_OBJ_PROP_CHAR_AXIOM 229

#define COWL_HASH_INIT_CLS_ASSERT_AXIOM 233
#define COWL_HASH_INIT_SAME_IND_AXIOM 239
#define COWL_HASH_INIT_DIFF_IND_AXIOM 241
#define COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM 251
#define COWL_HASH_INIT_NEG_OBJ_PROP_ASSERT_AXIOM 257
#define COWL_HASH_INIT_DATA_PROP_ASSERT_AXIOM 263
#define COWL_HASH_INIT_NEG_DATA_PROP_ASSERT_AXIOM 269

#define COWL_HASH_INIT_ONTO_ID 997

#define cowl_hash_iter(hash_acc, hash_new) ((hash_acc) * COWL_HASH_MULT + (hash_new))

#define cowl_hash_1(init, a) (cowl_hash_iter(init, a))
#define cowl_hash_2(init, a, b) (cowl_hash_iter(cowl_hash_iter(init, a), b))
#define cowl_hash_3(init, a, b, c) (cowl_hash_iter(cowl_hash_iter(cowl_hash_iter(init, a), b), c))
#define cowl_hash_4(init, a, b, c, d) \
    (cowl_hash_iter(cowl_hash_iter(cowl_hash_iter(cowl_hash_iter(init, a), b), c), d))

#endif // COWL_HASH_UTILS_H
