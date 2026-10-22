/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# सचे defined(__cplusplus) && __cplusplus >= 201103L
#अन्तर्भाव <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# सचे defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#अन्तर्भाव <inttypes.h>
#  define YYFLEX_USE_STDINT
# अञ्ञथा
#  सचे defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#अन्तर्भाव <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
प्रकारनिर्देश int8_t flex_int8_t;
प्रकारनिर्देश uint8_t flex_uint8_t;
प्रकारनिर्देश int16_t flex_int16_t;
प्रकारनिर्देश uint16_t flex_uint16_t;
प्रकारनिर्देश int32_t flex_int32_t;
प्रकारनिर्देश uint32_t flex_uint32_t;
# अञ्ञथा
प्रकारनिर्देश unsigned वर्ण flex_uint8_t;
प्रकारनिर्देश short पूर्णाङ्क flex_int16_t;
प्रकारनिर्देश unsigned short पूर्णाङ्क flex_uint16_t;
#  ifdef __STDC__
प्रकारनिर्देश signed वर्ण flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#अन्तर्भाव <climits>
#   अञ्ञथा
#अन्तर्भाव <limits.h>
#   endif
#   सचे UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
प्रकारनिर्देश पूर्णाङ्क flex_int32_t;
प्रकारनिर्देश unsigned पूर्णाङ्क flex_uint32_t;
#   endif
#  अञ्ञथा
प्रकारनिर्देश वर्ण flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
प्रकारनिर्देश long पूर्णाङ्क flex_int32_t;
प्रकारनिर्देश unsigned long पूर्णाङ्क flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
