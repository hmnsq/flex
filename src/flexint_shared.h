/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# जर defined(__cplusplus) && __cplusplus >= 201103L
#अन्तर्भाव <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# जर defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#अन्तर्भाव <inttypes.h>
#  define YYFLEX_USE_STDINT
# अन्यथा
#  जर defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#अन्तर्भाव <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
प्रकारव्याख्या int8_t flex_int8_t;
प्रकारव्याख्या uint8_t flex_uint8_t;
प्रकारव्याख्या int16_t flex_int16_t;
प्रकारव्याख्या uint16_t flex_uint16_t;
प्रकारव्याख्या int32_t flex_int32_t;
प्रकारव्याख्या uint32_t flex_uint32_t;
# अन्यथा
प्रकारव्याख्या अचिन्हित अक्षर flex_uint8_t;
प्रकारव्याख्या लघु पूर्णांक flex_int16_t;
प्रकारव्याख्या अचिन्हित लघु पूर्णांक flex_uint16_t;
#  ifdef __STDC__
प्रकारव्याख्या चिन्हित अक्षर flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#अन्तर्भाव <climits>
#   अन्यथा
#अन्तर्भाव <limits.h>
#   endif
#   जर अच_पूर्णांक_उच्च >= 4294967295
#    define YYFLEX_INT32_DEFINED
प्रकारव्याख्या पूर्णांक flex_int32_t;
प्रकारव्याख्या अचिन्हित पूर्णांक flex_uint32_t;
#   endif
#  अन्यथा
प्रकारव्याख्या अक्षर flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
प्रकारव्याख्या दीर्घ पूर्णांक flex_int32_t;
प्रकारव्याख्या अचिन्हित दीर्घ पूर्णांक flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
