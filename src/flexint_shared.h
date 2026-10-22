/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# જો defined(__cplusplus) && __cplusplus >= 201103L
#અન્તર્ભાવ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# જો defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#અન્તર્ભાવ <inttypes.h>
#  define YYFLEX_USE_STDINT
# નહીંતર
#  જો defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#અન્તર્ભાવ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
પ્રકારવ્યાખ્યા int8_t flex_int8_t;
પ્રકારવ્યાખ્યા uint8_t flex_uint8_t;
પ્રકારવ્યાખ્યા int16_t flex_int16_t;
પ્રકારવ્યાખ્યા uint16_t flex_uint16_t;
પ્રકારવ્યાખ્યા int32_t flex_int32_t;
પ્રકારવ્યાખ્યા uint32_t flex_uint32_t;
# નહીંતર
પ્રકારવ્યાખ્યા unsigned અક્ષર flex_uint8_t;
પ્રકારવ્યાખ્યા short પૂર્ણાંક flex_int16_t;
પ્રકારવ્યાખ્યા unsigned short પૂર્ણાંક flex_uint16_t;
#  ifdef __STDC__
પ્રકારવ્યાખ્યા signed અક્ષર flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#અન્તર્ભાવ <climits>
#   નહીંતર
#અન્તર્ભાવ <limits.h>
#   endif
#   જો UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
પ્રકારવ્યાખ્યા પૂર્ણાંક flex_int32_t;
પ્રકારવ્યાખ્યા unsigned પૂર્ણાંક flex_uint32_t;
#   endif
#  નહીંતર
પ્રકારવ્યાખ્યા અક્ષર flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
પ્રકારવ્યાખ્યા long પૂર્ણાંક flex_int32_t;
પ્રકારવ્યાખ્યા unsigned long પૂર્ણાંક flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
