/* flex integer type definitions */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ FLEXINT_H
#ವ್ಯಾಖ್ಯಾನಿಸು FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __STDC_LIMIT_MACROS
#ವ್ಯಾಖ್ಯಾನಿಸು __STDC_LIMIT_MACROS 1
#ಆದರೆ_ಅಂತ್ಯ

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#ಅನ್ತರ್ಭಾವ "flexint_shared.h"

/* Limits of integral types. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT8_MIN
#ವ್ಯಾಖ್ಯಾನಿಸು INT8_MIN               (-128)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT16_MIN
#ವ್ಯಾಖ್ಯಾನಿಸು INT16_MIN              (-32767-1)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT32_MIN
#ವ್ಯಾಖ್ಯಾನಿಸು INT32_MIN              (-2147483647-1)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT8_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು INT8_MAX               (127)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT16_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು INT16_MAX              (32767)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INT32_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು INT32_MAX              (2147483647)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ UINT8_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು UINT8_MAX              (255U)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ UINT16_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು UINT16_MAX             (65535U)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ UINT32_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು UINT32_MAX             (4294967295U)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ                ((ಪೂರ್ಣಾಂಕ)(~0U)>>1)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಗಾತ್ರ_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_MAX               (~(size_t)0)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* ! FLEXINT_H */
