/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEST_UTILS_H
#define COWL_TEST_UTILS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
uvec_decl(CowlError);

// Test utils

#define cowl_assert_equal(T, LHS, RHS)                                                              \
    utest_assert_wrap(cowl_##T##_equals(LHS, RHS), {                                                \
        CowlString *T##_lhs_str = cowl_##T##_to_string(LHS);                                        \
        CowlString *T##_rhs_str = cowl_##T##_to_string(RHS);                                        \
        printf(" must be equal to \"%s\", found \"%s\".",                                           \
               cowl_string_get_cstring(T##_rhs_str),                                                \
               cowl_string_get_cstring(T##_lhs_str));                                               \
        cowl_string_release(T##_lhs_str);                                                           \
        cowl_string_release(T##_rhs_str);                                                           \
    }, #LHS)

#define cowl_assert_not_equal(T, LHS, RHS)                                                          \
    utest_assert_wrap(!cowl_##T##_equals(LHS, RHS), {                                               \
        CowlString *T##_rhs_str = cowl_##T##_to_string(RHS);                                        \
        printf(" must not be equal to \"%s\".", cowl_string_get_cstring(T##_rhs_str));              \
        cowl_string_release(T##_rhs_str);                                                           \
    }, #LHS)

// Test data

#define COWL_TEST_ONTOLOGY "test_onto.owl"

CowlOntology* cowl_test_load_import(void *ctx, CowlIRI *iri);

COWL_END_DECLS

#endif // COWL_TEST_UTILS_H
