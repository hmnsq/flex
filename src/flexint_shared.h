/* flex integer type definitions */

#నిర్వచితం_కాకపోతే YYFLEX_INTTYPES_DEFINED
#నిర్వచించు YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ఒకవేళ defined(__cplusplus) && __cplusplus >= 201103L
#అన్తర్భావ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ఒకవేళ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#అన్తర్భావ <inttypes.h>
#  define YYFLEX_USE_STDINT
# లేకపోతే
#  ఒకవేళ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#అన్తర్భావ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
రకనిర్వచనం int8_t flex_int8_t;
రకనిర్వచనం uint8_t flex_uint8_t;
రకనిర్వచనం int16_t flex_int16_t;
రకనిర్వచనం uint16_t flex_uint16_t;
రకనిర్వచనం int32_t flex_int32_t;
రకనిర్వచనం uint32_t flex_uint32_t;
# లేకపోతే
రకనిర్వచనం గుర్తులేని అక్షరం flex_uint8_t;
రకనిర్వచనం పొట్టి పూర్ణాంకం flex_int16_t;
రకనిర్వచనం గుర్తులేని పొట్టి పూర్ణాంకం flex_uint16_t;
#  ifdef __STDC__
రకనిర్వచనం గుర్తుగల అక్షరం flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#అన్తర్భావ <climits>
#   లేకపోతే
#అన్తర్భావ <limits.h>
#   endif
#   ఒకవేళ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
రకనిర్వచనం పూర్ణాంకం flex_int32_t;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం flex_uint32_t;
#   endif
#  లేకపోతే
రకనిర్వచనం అక్షరం flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
రకనిర్వచనం దీర్ఘ పూర్ణాంకం flex_int32_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ పూర్ణాంకం flex_uint32_t;
#  endif
# endif
#అయితే_ముగింపు /* YYFLEX_INTTYPES_DEFINED */
