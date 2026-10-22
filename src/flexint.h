/* flex integer type definitions */

#اگر_غیر_تعریف_شدہ FLEXINT_H
#تعریف_کرو FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#اگر_غیر_تعریف_شدہ __STDC_LIMIT_MACROS
#تعریف_کرو __STDC_LIMIT_MACROS 1
#اگر_ختم

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#شامل "flexint_shared.h"

/* Limits of integral types. */
#اگر_غیر_تعریف_شدہ INT8_MIN
#تعریف_کرو INT8_MIN               (-128)
#اگر_ختم
#اگر_غیر_تعریف_شدہ INT16_MIN
#تعریف_کرو INT16_MIN              (-32767-1)
#اگر_ختم
#اگر_غیر_تعریف_شدہ INT32_MIN
#تعریف_کرو INT32_MIN              (-2147483647-1)
#اگر_ختم
#اگر_غیر_تعریف_شدہ INT8_MAX
#تعریف_کرو INT8_MAX               (127)
#اگر_ختم
#اگر_غیر_تعریف_شدہ INT16_MAX
#تعریف_کرو INT16_MAX              (32767)
#اگر_ختم
#اگر_غیر_تعریف_شدہ INT32_MAX
#تعریف_کرو INT32_MAX              (2147483647)
#اگر_ختم
#اگر_غیر_تعریف_شدہ UINT8_MAX
#تعریف_کرو UINT8_MAX              (255U)
#اگر_ختم
#اگر_غیر_تعریف_شدہ UINT16_MAX
#تعریف_کرو UINT16_MAX             (65535U)
#اگر_ختم
#اگر_غیر_تعریف_شدہ UINT32_MAX
#تعریف_کرو UINT32_MAX             (4294967295U)
#اگر_ختم

#اگر_غیر_تعریف_شدہ زیادہ_سے_زیادہ_عدد
#تعریف_کرو زیادہ_سے_زیادہ_عدد                ((صحیح)(~0U)>>1)
#اگر_ختم
#اگر_غیر_تعریف_شدہ سائز_MAX
#تعریف_کرو سائز_MAX               (~(size_t)0)
#اگر_ختم

#اگر_ختم /* ! FLEXINT_H */
