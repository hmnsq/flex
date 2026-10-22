/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ប្រសិនបើ defined(__cplusplus) && __cplusplus >= 201103L
#include <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ប្រសិនបើ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#include <inttypes.h>
#  define YYFLEX_USE_STDINT
# បើមិនដូច្នេះ
#  ប្រសិនបើ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#include <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
typedef int8_t flex_int8_t;
typedef uint8_t flex_uint8_t;
typedef int16_t flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t flex_int32_t;
typedef uint32_t flex_uint32_t;
# បើមិនដូច្នេះ
typedef unsigned var_na flex_uint8_t;
typedef short ចំនួនគត់ flex_int16_t;
typedef unsigned short ចំនួនគត់ flex_uint16_t;
#  ifdef __STDC__
typedef signed var_na flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#include <climits>
#   បើមិនដូច្នេះ
#include <limits.h>
#   endif
#   ប្រសិនបើ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
typedef ចំនួនគត់ flex_int32_t;
typedef unsigned ចំនួនគត់ flex_uint32_t;
#   endif
#  បើមិនដូច្នេះ
typedef var_na flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
typedef long ចំនួនគត់ flex_int32_t;
typedef unsigned long ចំនួនគត់ flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
