/* flex integer type definitions */

#اگر_غیر_تعریف_شدہ YYFLEX_INTTYPES_DEFINED
#تعریف_کرو YYFLEX_INTTYPES_DEFINED

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
# ورنہ
#  اگر defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#شامل <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
قسمتعریف int8_t flex_int8_t;
قسمتعریف uint8_t flex_uint8_t;
قسمتعریف int16_t flex_int16_t;
قسمتعریف uint16_t flex_uint16_t;
قسمتعریف int32_t flex_int32_t;
قسمتعریف uint32_t flex_uint32_t;
# ورنہ
قسمتعریف غیرعلامتی حرف flex_uint8_t;
قسمتعریف مختصر صحیح flex_int16_t;
قسمتعریف غیرعلامتی مختصر صحیح flex_uint16_t;
#  ifdef __STDC__
قسمتعریف علامتی حرف flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#شامل <climits>
#   ورنہ
#شامل <limits.h>
#   endif
#   اگر UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
قسمتعریف صحیح flex_int32_t;
قسمتعریف غیرعلامتی صحیح flex_uint32_t;
#   endif
#  ورنہ
قسمتعریف حرف flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
قسمتعریف طویل صحیح flex_int32_t;
قسمتعریف غیرعلامتی طویل صحیح flex_uint32_t;
#  endif
# endif
#اگر_ختم /* YYFLEX_INTTYPES_DEFINED */
