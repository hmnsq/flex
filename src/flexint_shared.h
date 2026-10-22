/* flex integer type definitions */

#ifndef YYFLEX_INTTYPES_DEFINED
#define YYFLEX_INTTYPES_DEFINED

/* Prefer C99 integer types if available. */

# എങ്കിൽ defined(__cplusplus) && __cplusplus >= 201103L
#അന്തര്ഭാവ <cstdint>
#  define YYFLEX_USE_STDINT
# endif
# എങ്കിൽ defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* Include <inttypes.h> and not <stdint.h> because Solaris 2.6 has the former
 * and not the latter.
 */
#അന്തര്ഭാവ <inttypes.h>
#  define YYFLEX_USE_STDINT
# അല്ലെങ്കിൽ
#  എങ്കിൽ defined(_MSC_VER) && _MSC_VER >= 1600
/* Visual C++ 2010 does not define __STDC_VERSION__ and has <stdint.h> but not
 * <inttypes.h>.
 */
#അന്തര്ഭാവ <stdint.h>
#   define YYFLEX_USE_STDINT
#  endif
# endif
# ifdef YYFLEX_USE_STDINT
തരനിർവചനം int8_t flex_int8_t;
തരനിർവചനം uint8_t flex_uint8_t;
തരനിർവചനം int16_t flex_int16_t;
തരനിർവചനം uint16_t flex_uint16_t;
തരനിർവചനം int32_t flex_int32_t;
തരനിർവചനം uint32_t flex_uint32_t;
# അല്ലെങ്കിൽ
തരനിർവചനം unsigned അക്ഷരം flex_uint8_t;
തരനിർവചനം short പൂർണ്ണസംഖ്യ flex_int16_t;
തരനിർവചനം unsigned short പൂർണ്ണസംഖ്യ flex_uint16_t;
#  ifdef __STDC__
തരനിർവചനം signed അക്ഷരം flex_int8_t;
/* ISO C only requires at least 16 bits for int. */
#   ifdef __cplusplus
#അന്തര്ഭാവ <climits>
#   അല്ലെങ്കിൽ
#അന്തര്ഭാവ <limits.h>
#   endif
#   എങ്കിൽ UINT_MAX >= 4294967295
#    define YYFLEX_INT32_DEFINED
തരനിർവചനം പൂർണ്ണസംഖ്യ flex_int32_t;
തരനിർവചനം unsigned പൂർണ്ണസംഖ്യ flex_uint32_t;
#   endif
#  അല്ലെങ്കിൽ
തരനിർവചനം അക്ഷരം flex_int8_t;
#  endif
#  ifndef YYFLEX_INT32_DEFINED
തരനിർവചനം long പൂർണ്ണസംഖ്യ flex_int32_t;
തരനിർവചനം unsigned long പൂർണ്ണസംഖ്യ flex_uint32_t;
#  endif
# endif
#endif /* YYFLEX_INTTYPES_DEFINED */
