/* flex integer type definitions */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ FLEXINT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __STDC_LIMIT_MACROS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __STDC_LIMIT_MACROS 1
#ਜੇ_ਅੰਤ

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ "flexint_shared.h"

/* Limits of integral types. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT8_MIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT8_MIN               (-128)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT16_MIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT16_MIN              (-32767-1)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT32_MIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT32_MIN              (-2147483647-1)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT8_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT8_MAX               (127)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT16_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT16_MAX              (32767)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INT32_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INT32_MAX              (2147483647)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ UINT8_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UINT8_MAX              (255U)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ UINT16_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UINT16_MAX             (65535U)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ UINT32_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UINT32_MAX             (4294967295U)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ                ((ਪੂਰਨ)(~0U)>>1)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਮਾਪ_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_MAX               (~(size_t)0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* ! FLEXINT_H */
