/**
 * Defines API attributes.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ATTRS_H
#define COWL_ATTRS_H

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

/**
 * Marks deprecated APIs.
 *
 * Deprecated APIs are usually replaced by alternatives, and will be removed in later
 * major versions of the library.
 *
 * @param msg Deprecation message.
 * @def COWL_DEPRECATED
 */

/**
 * Marks deprecated macros.
 *
 * Deprecated macros are usually replaced by alternatives, and will be removed in later
 * major versions of the library.
 *
 * @def COWL_DEPRECATED_MACRO
 */

#ifndef COWL_NO_DEPRECATED
#define COWL_DEPRECATED(msg) ULIB_DEPRECATED(msg)
#define COWL_DEPRECATED_MACRO ULIB_DEPRECATED_MACRO
#else
#define COWL_DEPRECATED(MSG)
#define COWL_DEPRECATED_MACRO
#endif

/// Suppresses unused variable warnings.
#define cowl_unused ulib_unused

#endif // COWL_ATTRS_H
