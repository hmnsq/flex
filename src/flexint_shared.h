/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ଯଦି defined(__cplusplus) && __cplusplus >= 201103L
#ଅନ୍ତର୍ଭାଵ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ଯଦି defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#  define YYFLEX_USE_STDINT
# ଅନ୍ୟଥା
#  ଯଦି defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
ପ୍ରକାରବ୍ୟାଖ୍ୟା int8_t flex_int8_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା uint8_t flex_uint8_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା int16_t flex_int16_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t flex_uint16_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା int32_t flex_int32_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t flex_uint32_t;
# ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ଅକ୍ଷର flex_uint8_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା short ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_int16_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned short ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_uint16_t;
#  ifdef __STDC__
ପ୍ରକାରବ୍ୟାଖ୍ୟା signed ଅକ୍ଷର flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#ଅନ୍ତର୍ଭାଵ <climits>
#   ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ <limits.h>
#   endif
#   ଯଦି UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_int32_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_uint32_t;
#   endif
#  ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅକ୍ଷର flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
ପ୍ରକାରବ୍ୟାଖ୍ୟା long ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_int32_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
