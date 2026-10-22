/* flex integer type definitions */

#यदि_अपरिभाषितम् FLEXINT_H
#परिभाषय FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#यदि_अपरिभाषितम् __STDC_LIMIT_MACROS
#परिभाषय __STDC_LIMIT_MACROS 1
#यदि_अन्तः

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#अन्तर्भाव "flexint_shared.h"

/* Limits of integral types. */
#यदि_अपरिभाषितम् INT8_MIN
#परिभाषय INT8_MIN               (-128)
#यदि_अन्तः
#यदि_अपरिभाषितम् INT16_MIN
#परिभाषय INT16_MIN              (-32767-1)
#यदि_अन्तः
#यदि_अपरिभाषितम् INT32_MIN
#परिभाषय INT32_MIN              (-2147483647-1)
#यदि_अन्तः
#यदि_अपरिभाषितम् INT8_MAX
#परिभाषय INT8_MAX               (127)
#यदि_अन्तः
#यदि_अपरिभाषितम् INT16_MAX
#परिभाषय INT16_MAX              (32767)
#यदि_अन्तः
#यदि_अपरिभाषितम् INT32_MAX
#परिभाषय INT32_MAX              (2147483647)
#यदि_अन्तः
#यदि_अपरिभाषितम् UINT8_MAX
#परिभाषय UINT8_MAX              (255U)
#यदि_अन्तः
#यदि_अपरिभाषितम् UINT16_MAX
#परिभाषय UINT16_MAX             (65535U)
#यदि_अन्तः
#यदि_अपरिभाषितम् UINT32_MAX
#परिभाषय UINT32_MAX             (4294967295U)
#यदि_अन्तः

#यदि_अपरिभाषितम् अधिकतम_पूर्णाङ्कः
#परिभाषय अधिकतम_पूर्णाङ्कः                ((पूर्णाङ्क)(~0U)>>1)
#यदि_अन्तः
#यदि_अपरिभाषितम् आकार_MAX
#परिभाषय आकार_MAX               (~(size_t)0)
#यदि_अन्तः

#यदि_अन्तः /* ! FLEXINT_H */
