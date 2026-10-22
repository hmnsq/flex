/* flex integer type definitions */

#నిర్వచితం_కాకపోతే FLEXINT_H
#నిర్వచించు FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#నిర్వచితం_కాకపోతే __STDC_LIMIT_MACROS
#నిర్వచించు __STDC_LIMIT_MACROS 1
#అయితే_ముగింపు

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#అన్తర్భావ "flexint_shared.h"

/* Limits of integral types. */
#నిర్వచితం_కాకపోతే INT8_MIN
#నిర్వచించు INT8_MIN               (-128)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే INT16_MIN
#నిర్వచించు INT16_MIN              (-32767-1)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే INT32_MIN
#నిర్వచించు INT32_MIN              (-2147483647-1)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే INT8_MAX
#నిర్వచించు INT8_MAX               (127)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే INT16_MAX
#నిర్వచించు INT16_MAX              (32767)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే INT32_MAX
#నిర్వచించు INT32_MAX              (2147483647)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే UINT8_MAX
#నిర్వచించు UINT8_MAX              (255U)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే UINT16_MAX
#నిర్వచించు UINT16_MAX             (65535U)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే UINT32_MAX
#నిర్వచించు UINT32_MAX             (4294967295U)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే గరిష్ఠ_పూర్ణాంకం
#నిర్వచించు గరిష్ఠ_పూర్ణాంకం                ((పూర్ణాంకం)(~0U)>>1)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే కొలత_MAX
#నిర్వచించు కొలత_MAX               (~(size_t)0)
#అయితే_ముగింపు

#అయితే_ముగింపు /* ! FLEXINT_H */
