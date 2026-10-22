/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# اگر defined(__cplusplus) && __cplusplus >= 201103L
#شامل <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# اگر defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#شامل <inttypes.h>
#  define YYFLEX_USE_STDINT
# وگرنه
#  اگر defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#شامل <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
تعریفنوع int8_t flex_int8_t;
تعریفنوع uint8_t flex_uint8_t;
تعریفنوع int16_t flex_int16_t;
تعریفنوع uint16_t flex_uint16_t;
تعریفنوع int32_t flex_int32_t;
تعریفنوع uint32_t flex_uint32_t;
# وگرنه
تعریفنوع unsigned نویسه flex_uint8_t;
تعریفنوع short صحیح flex_int16_t;
تعریفنوع unsigned short صحیح flex_uint16_t;
#  ifdef __STDC__
تعریفنوع signed نویسه flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#شامل <climits>
#   وگرنه
#شامل <limits.h>
#   endif
#   اگر UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
تعریفنوع صحیح flex_int32_t;
تعریفنوع unsigned صحیح flex_uint32_t;
#   endif
#  وگرنه
تعریفنوع نویسه flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
تعریفنوع long صحیح flex_int32_t;
تعریفنوع unsigned long صحیح flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
