/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# ಯದಿ defined(__cplusplus) && __cplusplus >= 201103L
#ಅನ್ತರ್ಭಾವ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# ಯದಿ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#ಅನ್ತರ್ಭಾವ <inttypes.h>
#  define YYFLEX_USE_STDINT
# ಅನ್ಯಥಾ
#  ಯದಿ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#ಅನ್ತರ್ಭಾವ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
ಪ್ರಕಾರನಿರ್ದೇಶ int8_t flex_int8_t;
ಪ್ರಕಾರನಿರ್ದೇಶ uint8_t flex_uint8_t;
ಪ್ರಕಾರನಿರ್ದೇಶ int16_t flex_int16_t;
ಪ್ರಕಾರನಿರ್ದೇಶ uint16_t flex_uint16_t;
ಪ್ರಕಾರನಿರ್ದೇಶ int32_t flex_int32_t;
ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t flex_uint32_t;
# ಅನ್ಯಥಾ
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ವರ್ಣ flex_uint8_t;
ಪ್ರಕಾರನಿರ್ದೇಶ short ಪೂರ್ಣಾಙ್ಕ flex_int16_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned short ಪೂರ್ಣಾಙ್ಕ flex_uint16_t;
#  ifdef __STDC__
ಪ್ರಕಾರನಿರ್ದೇಶ signed ವರ್ಣ flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#ಅನ್ತರ್ಭಾವ <climits>
#   ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ <limits.h>
#   endif
#   ಯದಿ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ flex_int32_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ಪೂರ್ಣಾಙ್ಕ flex_uint32_t;
#   endif
#  ಅನ್ಯಥಾ
ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
ಪ್ರಕಾರನಿರ್ದೇಶ long ಪೂರ್ಣಾಙ್ಕ flex_int32_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long ಪೂರ್ಣಾಙ್ಕ flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
