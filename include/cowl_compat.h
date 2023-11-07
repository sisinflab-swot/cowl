/**
 * Defines miscellaneous compatibility macros.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_COMPAT_H
#define COWL_COMPAT_H

#include "ulib.h"

// clang-format off

/// Marks the beginning of declarations.
#define COWL_BEGIN_DECLS ULIB_BEGIN_DECLS

/// Marks the end of declarations.
#define COWL_END_DECLS ULIB_END_DECLS

/**
 * Marks public API, whose symbols should be exported.
 * @def COWL_API
 */
#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef COWL_SHARED
        #ifdef COWL_BUILDING
            #define COWL_DLL_SPEC dllexport
        #else
            #define COWL_DLL_SPEC dllimport
        #endif
        #ifdef __GNUC__
            #define COWL_API __attribute__((COWL_DLL_SPEC))
        #else
            #define COWL_API __declspec(COWL_DLL_SPEC)
        #endif
    #else
        #define COWL_API
    #endif
#else
    #if __GNUC__ >= 4
        #define COWL_API __attribute__((__visibility__("default")))
    #else
        #define COWL_API
    #endif
#endif

/// Marks inline function definitions.
#define COWL_INLINE ULIB_INLINE

/// Marks pure functions.
#define COWL_PURE ULIB_PURE

/// Marks const functions.
#define COWL_CONST ULIB_CONST

/// Marks functions that return retained instances.
#define COWL_RETAINED // No-op

/// Suppresses unused variable warnings.
#define cowl_unused ulib_unused

/**
 * Struct type forward declaration.
 *
 * @param NAME Name of the struct type.
 */
#define cowl_struct_decl(NAME) typedef struct NAME NAME

/**
 * Checks whether the specified enum value is valid.
 *
 * @param T Enumeration name.
 * @param VAL Enumeration value.
 * @return True if the value is valid, false otherwise.
 */
#define cowl_enum_value_is_valid(T, VAL) ((unsigned)(VAL) < COWL_##T##_COUNT)

#endif // COWL_COMPAT_H
