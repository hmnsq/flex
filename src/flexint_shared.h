/* flex integer type definitions */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ YYFLEX_INTTYPES_DEFINED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ਜੇ defined(__cplusplus) && __cplusplus >= 201103L
#ਅਨ੍ਤਰ੍ਭਾਵ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ਜੇ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#  define YYFLEX_USE_STDINT
# ਨਹੀਂਤਾਂ
#  ਜੇ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int8_t flex_int8_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint8_t flex_uint8_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int16_t flex_int16_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t flex_uint16_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t flex_int32_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t flex_uint32_t;
# ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ flex_uint8_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਛੋਟਾ ਪੂਰਨ flex_int16_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਪੂਰਨ flex_uint16_t;
#  ifdef __STDC__
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#ਅਨ੍ਤਰ੍ਭਾਵ <climits>
#   ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#   endif
#   ਜੇ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ flex_int32_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flex_uint32_t;
#   endif
#  ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ ਪੂਰਨ flex_int32_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਪੂਰਨ flex_uint32_t;
#  endif
# endif
#ਜੇ_ਅੰਤ /* YYFLEX_INTTYPES_DEFINED */
