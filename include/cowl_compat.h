/**
 * Defines miscellaneous compatibility macros.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_COMPAT_H
#define COWL_COMPAT_H

#include "ulib.h"

/**
 * @def COWL_BEGIN_DECLS
 * Marks the beginning of declarations.
 */

/**
 * @def COWL_END_DECLS
 * Marks the end of declarations.
 */

#ifdef __cplusplus
    #define COWL_BEGIN_DECLS extern "C" {
    #define COWL_END_DECLS }
#else
    #define COWL_BEGIN_DECLS
    #define COWL_END_DECLS
#endif

/**
 * @def COWL_PUBLIC
 * Marks public API, whose symbols should be exported.
 */

/**
 * @def COWL_PRIVATE
 * Marks private API, whose symbols should not be exported.
 */

#if defined _WIN32 || defined __CYGWIN__
    #ifdef COWL_SHARED
        #ifdef COWL_BUILDING
            #define COWL_DLL_SPEC dllexport
        #else
            #define COWL_DLL_SPEC dllimport
        #endif
        #ifdef __GNUC__
            #define COWL_PUBLIC __attribute__ ((COWL_DLL_SPEC))
        #else
            #define COWL_PUBLIC __declspec(COWL_DLL_SPEC)
        #endif
    #else
        #define COWL_PUBLIC
    #endif
    #define COWL_PRIVATE
#else
    #if __GNUC__ >= 4
        #define COWL_PUBLIC __attribute__ ((visibility ("default")))
        #define COWL_PRIVATE  __attribute__ ((visibility ("hidden")))
    #else
        #define COWL_PUBLIC
        #define COWL_PRIVATE
    #endif
#endif

/// Suppresses unused variable warnings.
#ifndef cowl_unused
    #if (defined __clang__ && __clang_major__ >= 3) || (defined __GNUC__ && __GNUC__ >= 3)
        #define cowl_unused __attribute__((__unused__))
    #else
        #define cowl_unused
    #endif
#endif

/**
 * Struct type.
 *
 * @param NAME Name of the struct type.
 */
#define cowl_struct(NAME) struct NAME##_s

/**
 * Enum type.
 *
 * @param NAME Name of the enum type.
 */
#define cowl_enum(NAME) enum NAME##_e

/**
 * Struct type forward declaration.
 *
 * @param NAME Name of the struct type.
 */
#define cowl_struct_decl(NAME) typedef cowl_struct(NAME) NAME

/**
 * Enum type forward declaration.
 *
 * @param NAME Name of the enum type.
 */
#define cowl_enum_decl(NAME) typedef cowl_enum(NAME) NAME

/**
 * Vector type forward declaration.
 *
 * @param T Type of the vector elements.
 * @param NAME Name of the vector type.
 */
#define cowl_vector_decl(T, NAME)                                                                   \
    uvec_decl(T);                                                                                   \
    typedef struct UVec(T) const NAME

/**
 * Hash table type forward declaration.
 *
 * @param NAME Name of the hash table type.
 */
#define cowl_hash_decl(NAME)                                                                        \
    uhash_decl(NAME);                                                                               \
    typedef struct UHash(NAME) const NAME

#endif // COWL_COMPAT_H
