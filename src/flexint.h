/* flex integer type definitions */

#جے_بنا_تعریف FLEXINT_H
#تعریف_کرو FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#جے_بنا_تعریف __STDC_LIMIT_MACROS
#تعریف_کرو __STDC_LIMIT_MACROS 1
#جے_انت

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ضمن "flexint_shared.h"

/* Limits of integral types. */
#جے_بنا_تعریف INT8_MIN
#تعریف_کرو INT8_MIN               (-128)
#جے_انت
#جے_بنا_تعریف INT16_MIN
#تعریف_کرو INT16_MIN              (-32767-1)
#جے_انت
#جے_بنا_تعریف INT32_MIN
#تعریف_کرو INT32_MIN              (-2147483647-1)
#جے_انت
#جے_بنا_تعریف INT8_MAX
#تعریف_کرو INT8_MAX               (127)
#جے_انت
#جے_بنا_تعریف INT16_MAX
#تعریف_کرو INT16_MAX              (32767)
#جے_انت
#جے_بنا_تعریف INT32_MAX
#تعریف_کرو INT32_MAX              (2147483647)
#جے_انت
#جے_بنا_تعریف UINT8_MAX
#تعریف_کرو UINT8_MAX              (255U)
#جے_انت
#جے_بنا_تعریف UINT16_MAX
#تعریف_کرو UINT16_MAX             (65535U)
#جے_انت
#جے_بنا_تعریف UINT32_MAX
#تعریف_کرو UINT32_MAX             (4294967295U)
#جے_انت

#جے_بنا_تعریف ودھ_توں_ودھ_عدد
#تعریف_کرو ودھ_توں_ودھ_عدد                ((صحيح)(~0U)>>1)
#جے_انت
#جے_بنا_تعریف ناپ_MAX
#تعریف_کرو ناپ_MAX               (~(size_t)0)
#جے_انت

#جے_انت /* ! FLEXINT_H */
