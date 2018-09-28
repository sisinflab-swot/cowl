/** @file
 * Defines miscellaneous compatibility macros.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_COMPAT_H
#define COWL_COMPAT_H

#ifdef __cplusplus
    #define COWL_BEGIN_DECLS extern "C" {
    #define COWL_END_DECLS }
#else
    #define COWL_BEGIN_DECLS
    #define COWL_END_DECLS
#endif

#ifndef cowl_unused
    #if (defined __clang__ && __clang_major__ >= 3) || (defined __GNUC__ && __GNUC__ >= 3)
        #define cowl_unused __attribute__((__unused__))
    #else
        #define cowl_unused
    #endif
#endif

#endif // COWL_COMPAT_H
