/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEST_UTILS_H
#define COWL_TEST_UTILS_H

#include "cowl_macros.h"
#include "cowl_std.h"

#include <stdio.h>

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
typedef vector_struct(CowlError) Vector(CowlError);

// Test utils

#define cowl_assert_wrap(EXP, CODE, ...) do {                                                       \
    if (!(EXP)) {                                                                                   \
        printf("Test failed: %s, line %d\nReason: ", __func__, __LINE__);                           \
        printf(__VA_ARGS__);                                                                        \
        CODE;                                                                                       \
        printf("\n");                                                                               \
        return false;                                                                               \
    }                                                                                               \
} while(0)

#define cowl_assert(EXP, ...) cowl_assert_wrap(EXP, , __VA_ARGS__)

#define cowl_assert_equal(T, LHS, RHS, ...)                                                         \
    cowl_assert_wrap(cowl_##T##_equals(LHS, RHS), {                                                 \
        CowlString *T##_lhs_str = cowl_##T##_to_string(LHS);                                        \
        CowlString *T##_rhs_str = cowl_##T##_to_string(RHS);                                        \
        printf(" must be equal to \"%s\", found \"%s\".",                                           \
               cowl_string_get_cstring(T##_rhs_str),                                                \
               cowl_string_get_cstring(T##_lhs_str));                                               \
        cowl_string_release(T##_lhs_str);                                                           \
        cowl_string_release(T##_rhs_str);                                                           \
    }, __VA_ARGS__)

#define cowl_assert_not_equal(T, LHS, RHS, ...)                                                     \
    cowl_assert_wrap(!cowl_##T##_equals(LHS, RHS), {                                                \
        CowlString *T##_rhs_str = cowl_##T##_to_string(RHS);                                        \
        printf(" must not be equal to \"%s\".", cowl_string_get_cstring(T##_rhs_str));              \
        cowl_string_release(T##_rhs_str);                                                           \
    }, __VA_ARGS__)

#define cowl_assert_equal_int(LHS, RHS, ...)                                                        \
    cowl_assert_wrap((LHS) == (RHS), {                                                              \
        printf(" must be equal to %d, found %d.", RHS, LHS);                                        \
    }, __VA_ARGS__)

#define cowl_assert_equal_str(LHS, RHS, ...)                                                        \
    cowl_assert_wrap(strcmp((LHS), (RHS)) == 0, {                                                   \
        printf(" must be equal to \"%s\", found \"%s\".", RHS, LHS);                                \
    }, __VA_ARGS__)

#define cowl_assert_not_null(EXP, ...) \
    cowl_assert_wrap(EXP, printf(" must not be NULL."), __VA_ARGS__)

// Test data

#define COWL_TEST_ONTOLOGY "test_onto.owl"

CowlOntology* cowl_test_load_import(void *ctx, CowlIRI *iri, Vector(CowlError) *errors);

COWL_END_DECLS

#endif // COWL_TEST_UTILS_H
