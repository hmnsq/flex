/* flex integer type definitions */

#که_نه_تعریف_شوی FLEXINT_H
#تعریف_کړه FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#که_نه_تعریف_شوی __STDC_LIMIT_MACROS
#تعریف_کړه __STDC_LIMIT_MACROS 1
#د_که_پای

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ضمن "flexint_shared.h"

/* Limits of integral types. */
#که_نه_تعریف_شوی INT8_MIN
#تعریف_کړه INT8_MIN               (-128)
#د_که_پای
#که_نه_تعریف_شوی INT16_MIN
#تعریف_کړه INT16_MIN              (-32767-1)
#د_که_پای
#که_نه_تعریف_شوی INT32_MIN
#تعریف_کړه INT32_MIN              (-2147483647-1)
#د_که_پای
#که_نه_تعریف_شوی INT8_MAX
#تعریف_کړه INT8_MAX               (127)
#د_که_پای
#که_نه_تعریف_شوی INT16_MAX
#تعریف_کړه INT16_MAX              (32767)
#د_که_پای
#که_نه_تعریف_شوی INT32_MAX
#تعریف_کړه INT32_MAX              (2147483647)
#د_که_پای
#که_نه_تعریف_شوی UINT8_MAX
#تعریف_کړه UINT8_MAX              (255U)
#د_که_پای
#که_نه_تعریف_شوی UINT16_MAX
#تعریف_کړه UINT16_MAX             (65535U)
#د_که_پای
#که_نه_تعریف_شوی UINT32_MAX
#تعریف_کړه UINT32_MAX             (4294967295U)
#د_که_پای

#که_نه_تعریف_شوی لوی_عدد
#تعریف_کړه لوی_عدد                ((صحيح)(~0U)>>1)
#د_که_پای
#که_نه_تعریف_شوی اندازه_MAX
#تعریف_کړه اندازه_MAX               (~(size_t)0)
#د_که_پای

#د_که_پای /* ! FLEXINT_H */
