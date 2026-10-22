/* flex integer type definitions */

#अगर_अघोषित FLEXINT_H
#घोषणा FLEXINT_H

/* C++ systems might need __STDC_LIMIT_MACROS defined before including
 * <stdint.h>, if you want the limit (max/min) macros for int types.
 */
#अगर_अघोषित __STDC_LIMIT_MACROS
#घोषणा __STDC_LIMIT_MACROS 1
#पूर्ण_अगर

/* "flexint_shared.h" will be included also in skeleton. It will include
 * <inttypes.h> (if available) and define flex's integral types.
 */
#समावेश "flexint_shared.h"

/* Limits of integral types. */
#अगर_अघोषित INT8_MIN
#घोषणा INT8_MIN               (-128)
#पूर्ण_अगर
#अगर_अघोषित INT16_MIN
#घोषणा INT16_MIN              (-32767-1)
#पूर्ण_अगर
#अगर_अघोषित INT32_MIN
#घोषणा INT32_MIN              (-2147483647-1)
#पूर्ण_अगर
#अगर_अघोषित INT8_MAX
#घोषणा INT8_MAX               (127)
#पूर्ण_अगर
#अगर_अघोषित INT16_MAX
#घोषणा INT16_MAX              (32767)
#पूर्ण_अगर
#अगर_अघोषित INT32_MAX
#घोषणा INT32_MAX              (2147483647)
#पूर्ण_अगर
#अगर_अघोषित UINT8_MAX
#घोषणा UINT8_MAX              (255U)
#पूर्ण_अगर
#अगर_अघोषित UINT16_MAX
#घोषणा UINT16_MAX             (65535U)
#पूर्ण_अगर
#अगर_अघोषित UINT32_MAX
#घोषणा UINT32_MAX             (4294967295U)
#पूर्ण_अगर

#अगर_अघोषित पूर्णांक_उच्च
#घोषणा पूर्णांक_उच्च                ((पूर्णांक)(~0U)>>1)
#पूर्ण_अगर
#अगर_अघोषित आकार_MAX
#घोषणा आकार_MAX               (~(माप_प्रकार)0)
#पूर्ण_अगर

#पूर्ण_अगर /* ! FLEXINT_H */
