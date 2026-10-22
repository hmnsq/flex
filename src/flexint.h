/* flex integer type definitions */

#جيڪڏهن_وصف_نه_ٿيل FLEXINT_H
#وصف_ڪريو FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#جيڪڏهن_وصف_نه_ٿيل __STDC_LIMIT_MACROS
#وصف_ڪريو __STDC_LIMIT_MACROS 1
#جيڪڏهن_پورو

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ضمن "flexint_shared.h"

/* Limits of integral types. */
#جيڪڏهن_وصف_نه_ٿيل INT8_MIN
#وصف_ڪريو INT8_MIN               (-128)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل INT16_MIN
#وصف_ڪريو INT16_MIN              (-32767-1)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل INT32_MIN
#وصف_ڪريو INT32_MIN              (-2147483647-1)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل INT8_MAX
#وصف_ڪريو INT8_MAX               (127)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل INT16_MAX
#وصف_ڪريو INT16_MAX              (32767)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل INT32_MAX
#وصف_ڪريو INT32_MAX              (2147483647)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل UINT8_MAX
#وصف_ڪريو UINT8_MAX              (255U)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل UINT16_MAX
#وصف_ڪريو UINT16_MAX             (65535U)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل UINT32_MAX
#وصف_ڪريو UINT32_MAX             (4294967295U)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل وڌ_کان_وڌ_عدد
#وصف_ڪريو وڌ_کان_وڌ_عدد                ((صحيح)(~0U)>>1)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل سائيز_MAX
#وصف_ڪريو سائيز_MAX               (~(size_t)0)
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* ! FLEXINT_H */
