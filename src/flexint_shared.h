/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# যদি defined(__cplusplus) && __cplusplus >= 201103L
#অন্তর্ভাব <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# যদি defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#অন্তর্ভাব <inttypes.h>
#  define YYFLEX_USE_STDINT
# অন্যথা
#  যদি defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#অন্তর্ভাব <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
প্রকারনির্দেশ int8_t flex_int8_t;
প্রকারনির্দেশ uint8_t flex_uint8_t;
প্রকারনির্দেশ int16_t flex_int16_t;
প্রকারনির্দেশ uint16_t flex_uint16_t;
প্রকারনির্দেশ int32_t flex_int32_t;
প্রকারনির্দেশ uint32_t flex_uint32_t;
# অন্যথা
প্রকারনির্দেশ unsigned বর্ণ flex_uint8_t;
প্রকারনির্দেশ short পূর্ণাঙ্ক flex_int16_t;
প্রকারনির্দেশ unsigned short পূর্ণাঙ্ক flex_uint16_t;
#  ifdef __STDC__
প্রকারনির্দেশ signed বর্ণ flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#অন্তর্ভাব <climits>
#   অন্যথা
#অন্তর্ভাব <limits.h>
#   endif
#   যদি UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
প্রকারনির্দেশ পূর্ণাঙ্ক flex_int32_t;
প্রকারনির্দেশ unsigned পূর্ণাঙ্ক flex_uint32_t;
#   endif
#  অন্যথা
প্রকারনির্দেশ বর্ণ flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
প্রকারনির্দেশ long পূর্ণাঙ্ক flex_int32_t;
প্রকারনির্দেশ unsigned long পূর্ণাঙ্ক flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
