/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# အကယ်၍ defined(__cplusplus) && __cplusplus >= 201103L
#include <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# အကယ်၍ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#include <inttypes.h>
#  define YYFLEX_USE_STDINT
# မဟုတ်ပါက
#  အကယ်၍ defined(_MSC_VER) && _MSC_VER >= 1600
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
# မဟုတ်ပါက
typedef unsigned var_na flex_uint8_t;
typedef short ကိန်းပြည့် flex_int16_t;
typedef unsigned short ကိန်းပြည့် flex_uint16_t;
#  ifdef __STDC__
typedef signed var_na flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#include <climits>
#   မဟုတ်ပါက
#include <limits.h>
#   endif
#   အကယ်၍ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
typedef ကိန်းပြည့် flex_int32_t;
typedef unsigned ကိန်းပြည့် flex_uint32_t;
#   endif
#  မဟုတ်ပါက
typedef var_na flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
typedef long ကိန်းပြည့် flex_int32_t;
typedef unsigned long ကိန်းပြည့် flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
