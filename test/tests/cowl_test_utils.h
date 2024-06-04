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

#include "cowl_attrs.h"
#include "cowl_macros.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
uvec_decl(CowlError);

// Test utils

#define cowl_assert_equal(T, LHS, RHS)                                                             \
    utest_assert_wrap(                                                                             \
        cowl_equals(LHS, RHS),                                                                     \
        {                                                                                          \
            UString T##_lhs_str = cowl_to_ustring(LHS);                                            \
            UString T##_rhs_str = cowl_to_ustring(RHS);                                            \
            printf(" must be equal to \"%s\", found \"%s\".", ustring_data(T##_rhs_str),           \
                   ustring_data(T##_lhs_str));                                                     \
            ustring_deinit(&T##_lhs_str);                                                          \
            ustring_deinit(&T##_rhs_str);                                                          \
        },                                                                                         \
        #LHS)

#define cowl_assert_not_equal(T, LHS, RHS)                                                         \
    utest_assert_wrap(                                                                             \
        !cowl_equals(LHS, RHS),                                                                    \
        {                                                                                          \
            UString T##_rhs_str = cowl_to_ustring(RHS);                                            \
            printf(" must not be equal to \"%s\".", ustring_data(T##_rhs_str));                    \
            ustring_deinit(&T##_rhs_str);                                                          \
        },                                                                                         \
        #LHS)

// Test data

#define COWL_TEST_ONTOLOGY "test_onto.owl"
#define COWL_TEST_IMPORT "test_import.owl"

CowlOntology *cowl_test_load_import(void *ctx, CowlIRI *iri);

COWL_END_DECLS

#endif // COWL_TEST_UTILS_H
