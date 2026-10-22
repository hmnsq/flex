/* flex integer type definitions */

#اگر_تعریف_نشده FLEXINT_H
#تعریف_کن FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#اگر_تعریف_نشده __STDC_LIMIT_MACROS
#تعریف_کن __STDC_LIMIT_MACROS 1
#پایان_اگر

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ضمن "flexint_shared.h"

/* Limits of integral types. */
#اگر_تعریف_نشده INT8_MIN
#تعریف_کن INT8_MIN               (-128)
#پایان_اگر
#اگر_تعریف_نشده INT16_MIN
#تعریف_کن INT16_MIN              (-32767-1)
#پایان_اگر
#اگر_تعریف_نشده INT32_MIN
#تعریف_کن INT32_MIN              (-2147483647-1)
#پایان_اگر
#اگر_تعریف_نشده INT8_MAX
#تعریف_کن INT8_MAX               (127)
#پایان_اگر
#اگر_تعریف_نشده INT16_MAX
#تعریف_کن INT16_MAX              (32767)
#پایان_اگر
#اگر_تعریف_نشده INT32_MAX
#تعریف_کن INT32_MAX              (2147483647)
#پایان_اگر
#اگر_تعریف_نشده UINT8_MAX
#تعریف_کن UINT8_MAX              (255U)
#پایان_اگر
#اگر_تعریف_نشده UINT16_MAX
#تعریف_کن UINT16_MAX             (65535U)
#پایان_اگر
#اگر_تعریف_نشده UINT32_MAX
#تعریف_کن UINT32_MAX             (4294967295U)
#پایان_اگر

#اگر_تعریف_نشده بیشترین_صحیح
#تعریف_کن بیشترین_صحیح                ((صحيح)(~0U)>>1)
#پایان_اگر
#اگر_تعریف_نشده اندازه_MAX
#تعریف_کن اندازه_MAX               (~(size_t)0)
#پایان_اگر

#پایان_اگر /* ! FLEXINT_H */
