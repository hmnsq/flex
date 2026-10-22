/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ܐܢ defined(__cplusplus) && __cplusplus >= 201103L
#ضمن <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ܐܢ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#ضمن <inttypes.h>
#  define YYFLEX_USE_STDINT
# ܐܚܪܢܐ
#  ܐܢ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#ضمن <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
تعريفنوع int8_t flex_int8_t;
تعريفنوع uint8_t flex_uint8_t;
تعريفنوع int16_t flex_int16_t;
تعريفنوع uint16_t flex_uint16_t;
تعريفنوع int32_t flex_int32_t;
تعريفنوع uint32_t flex_uint32_t;
# ܐܚܪܢܐ
تعريفنوع unsigned حرف flex_uint8_t;
تعريفنوع short صحيح flex_int16_t;
تعريفنوع unsigned short صحيح flex_uint16_t;
#  ifdef __STDC__
تعريفنوع signed حرف flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#ضمن <climits>
#   ܐܚܪܢܐ
#ضمن <limits.h>
#   endif
#   ܐܢ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
تعريفنوع صحيح flex_int32_t;
تعريفنوع unsigned صحيح flex_uint32_t;
#   endif
#  ܐܚܪܢܐ
تعريفنوع حرف flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
تعريفنوع long صحيح flex_int32_t;
تعريفنوع unsigned long صحيح flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
