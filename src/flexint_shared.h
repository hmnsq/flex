/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# எனில் defined(__cplusplus) && __cplusplus >= 201103L
#அந்தர்பாவ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# எனில் defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#அந்தர்பாவ <inttypes.h>
#  define YYFLEX_USE_STDINT
# இல்லையெனில்
#  எனில் defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#அந்தர்பாவ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
வகைவரை int8_t flex_int8_t;
வகைவரை uint8_t flex_uint8_t;
வகைவரை int16_t flex_int16_t;
வகைவரை uint16_t flex_uint16_t;
வகைவரை int32_t flex_int32_t;
வகைவரை uint32_t flex_uint32_t;
# இல்லையெனில்
வகைவரை unsigned எழுத்து flex_uint8_t;
வகைவரை short முழு flex_int16_t;
வகைவரை unsigned short முழு flex_uint16_t;
#  ifdef __STDC__
வகைவரை signed எழுத்து flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#அந்தர்பாவ <climits>
#   இல்லையெனில்
#அந்தர்பாவ <limits.h>
#   endif
#   எனில் UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
வகைவரை முழு flex_int32_t;
வகைவரை unsigned முழு flex_uint32_t;
#   endif
#  இல்லையெனில்
வகைவரை எழுத்து flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
வகைவரை long முழு flex_int32_t;
வகைவரை unsigned long முழு flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
