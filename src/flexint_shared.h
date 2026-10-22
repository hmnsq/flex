/* flex integer type definitions */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ YYFLEX_INTTYPES_DEFINED
#ವ್ಯಾಖ್ಯಾನಿಸು YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ಆದರೆ defined(__cplusplus) && __cplusplus >= 201103L
#ಅನ್ತರ್ಭಾವ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ಆದರೆ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#ಅನ್ತರ್ಭಾವ <inttypes.h>
#  define YYFLEX_USE_STDINT
# ಇಲ್ಲದಿದ್ದರೆ
#  ಆದರೆ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#ಅನ್ತರ್ಭಾವ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int8_t flex_int8_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint8_t flex_uint8_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int16_t flex_int16_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t flex_uint16_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t flex_int32_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t flex_uint32_t;
# ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ flex_uint8_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಗಿಡ್ಡ ಪೂರ್ಣಾಂಕ flex_int16_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ಪೂರ್ಣಾಂಕ flex_uint16_t;
#  ifdef __STDC__
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#ಅನ್ತರ್ಭಾವ <climits>
#   ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <limits.h>
#   endif
#   ಆದರೆ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ flex_int32_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flex_uint32_t;
#   endif
#  ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ flex_int32_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ flex_uint32_t;
#  endif
# endif
#ಆದರೆ_ಅಂತ್ಯ /* YYFLEX_INTTYPES_DEFINED */
