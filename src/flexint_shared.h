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
প্রকারলেখ int8_t flex_int8_t;
প্রকারলেখ uint8_t flex_uint8_t;
প্রকারলেখ int16_t flex_int16_t;
প্রকারলেখ uint16_t flex_uint16_t;
প্রকারলেখ int32_t flex_int32_t;
প্রকারলেখ uint32_t flex_uint32_t;
# অন্যথা
প্রকারলেখ unsigned অক্ষর flex_uint8_t;
প্রকারলেখ short পূর্ণসংখ্যা flex_int16_t;
প্রকারলেখ unsigned short পূর্ণসংখ্যা flex_uint16_t;
#  ifdef __STDC__
প্রকারলেখ signed অক্ষর flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#অন্তর্ভাব <climits>
#   অন্যথা
#অন্তর্ভাব <limits.h>
#   endif
#   যদি UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
প্রকারলেখ পূর্ণসংখ্যা flex_int32_t;
প্রকারলেখ unsigned পূর্ণসংখ্যা flex_uint32_t;
#   endif
#  অন্যথা
প্রকারলেখ অক্ষর flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
প্রকারলেখ long পূর্ণসংখ্যা flex_int32_t;
প্রকারলেখ unsigned long পূর্ণসংখ্যা flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
