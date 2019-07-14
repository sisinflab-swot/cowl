/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

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

#define COWL_HASH_INIT_DATA_COMPL 37
#define COWL_HASH_INIT_DATA_ONE_OF 41
#define COWL_HASH_INIT_DATA_NARY 43
#define COWL_HASH_INIT_DATA_QUANT 47
#define COWL_HASH_INIT_DATA_CARD 53
#define COWL_HASH_INIT_DATA_HAS_VALUE 59
#define COWL_HASH_INIT_DATA_RESTR 61

#define COWL_HASH_INIT_FACET_RESTR 67
#define COWL_HASH_INIT_LITERAL 71
#define COWL_HASH_INIT_ANNOTATION 73

#define COWL_HASH_INIT_DECL_AXIOM 179
#define COWL_HASH_INIT_SUBCLASS_AXIOM 181
#define COWL_HASH_INIT_NARY_CLS_AXIOM 191
#define COWL_HASH_INIT_DISJ_UNION_AXIOM 193

#define COWL_HASH_INIT_SUB_OBJ_PROP_AXIOM 197
#define COWL_HASH_INIT_SUB_OBJ_PROP_CHAIN_AXIOM 199
#define COWL_HASH_INIT_NARY_OBJ_PROP_AXIOM 211
#define COWL_HASH_INIT_INV_OBJ_PROP_AXIOM 223
#define COWL_HASH_INIT_OBJ_PROP_DOMAIN_AXIOM 227
#define COWL_HASH_INIT_OBJ_PROP_RANGE_AXIOM 229
#define COWL_HASH_INIT_OBJ_PROP_CHAR_AXIOM 233

#define COWL_HASH_INIT_SUB_DATA_PROP_AXIOM 239
#define COWL_HASH_INIT_NARY_DATA_PROP_AXIOM 241
#define COWL_HASH_INIT_FUNCTIONAL_DATA_PROP_AXIOM 251
#define COWL_HASH_INIT_DATA_PROP_DOMAIN_AXIOM 257
#define COWL_HASH_INIT_DATA_PROP_RANGE_AXIOM 263
#define COWL_HASH_INIT_DATATYPE_DEF_AXIOM 269

#define COWL_HASH_INIT_CLS_ASSERT_AXIOM 271
#define COWL_HASH_INIT_NARY_IND_AXIOM 277
#define COWL_HASH_INIT_OBJ_PROP_ASSERT_AXIOM 281
#define COWL_HASH_INIT_DATA_PROP_ASSERT_AXIOM 283
#define COWL_HASH_INIT_HAS_KEY_AXIOM 293

#define COWL_HASH_INIT_ANNOT_ASSERT_AXIOM 307
#define COWL_HASH_INIT_SUB_ANNOT_PROP_AXIOM 311
#define COWL_HASH_INIT_ANNOT_PROP_DOMAIN_AXIOM 313
#define COWL_HASH_INIT_ANNOT_PROP_RANGE_AXIOM 317

#define COWL_HASH_INIT_ONTO_ID 997

#define cowl_hash_iter(hash_acc, hash_new) ((hash_acc) * COWL_HASH_MULT + (hash_new))

#define cowl_hash_1(init, a) (cowl_hash_iter(init, a))
#define cowl_hash_2(init, a, b) (cowl_hash_iter(cowl_hash_1(init, a), b))
#define cowl_hash_3(init, a, b, c) (cowl_hash_iter(cowl_hash_2(init, a, b), c))
#define cowl_hash_4(init, a, b, c, d) (cowl_hash_iter(cowl_hash_3(init, a, b, c), d))
#define cowl_hash_5(init, a, b, c, d, e) (cowl_hash_iter(cowl_hash_4(init, a, b, c, d), e))

#endif // COWL_HASH_UTILS_H
