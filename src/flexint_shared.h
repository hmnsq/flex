/* flex integer type definitions */

#अगर_अघोषित YYFLEX_INTTYPES_DEFINED
#घोषणा YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# अगर defined(__cplusplus) && __cplusplus >= 201103L
#समावेश <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# अगर defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#समावेश <inttypes.h>
#  define YYFLEX_USE_STDINT
# अन्यथा
#  अगर defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#समावेश <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
प्रकार int8_t flex_int8_t;
प्रकार uint8_t flex_uint8_t;
प्रकार int16_t flex_int16_t;
प्रकार uint16_t flex_uint16_t;
प्रकार int32_t flex_int32_t;
प्रकार uint32_t flex_uint32_t;
# अन्यथा
प्रकार अचिन्हित अक्षर flex_uint8_t;
प्रकार लघु पूर्णांक flex_int16_t;
प्रकार अचिन्हित लघु पूर्णांक flex_uint16_t;
#  ifdef __STDC__
प्रकार चिन्हित अक्षर flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#समावेश <climits>
#   अन्यथा
#समावेश <limits.h>
#   endif
#   अगर अच_पूर्णांक_उच्च >= 4294967295
#    define YYFLEX_INT32_DEFINED
प्रकार पूर्णांक flex_int32_t;
प्रकार अचिन्हित पूर्णांक flex_uint32_t;
#   endif
#  अन्यथा
प्रकार अक्षर flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
प्रकार दीर्घ पूर्णांक flex_int32_t;
प्रकार अचिन्हित दीर्घ पूर्णांक flex_uint32_t;
#  endif
# endif
#पूर्ण_अगर /* YYFLEX_INTTYPES_DEFINED */
