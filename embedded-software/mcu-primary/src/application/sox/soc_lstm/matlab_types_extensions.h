#ifndef MATLAB_TYPES_EXTENSION_H_
#define MATLAB_TYPES_EXTENSION_H_

#include <stdint.h>  // For standard types
#include "matlab_types.h"  // Base foxBMS types

#ifndef real32_T
typedef float real32_T;
#endif

#ifndef real64_T
typedef double real64_T;
#endif

#ifndef int8_T
typedef int8_t int8_T;
#endif

#ifndef uint8_T
typedef uint8_t uint8_T;
#endif

#ifndef int16_T
typedef int16_t int16_T;
#endif

#ifndef uint16_T
typedef uint16_t uint16_T;
#endif

#ifndef uint32_T
typedef uint32_t uint32_T;
#endif

#ifndef boolean_T
typedef int boolean_T;
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef MAX_int32_T
#define MAX_int32_T 2147483647
#endif

#ifndef MIN_int32_T
#define MIN_int32_T (-2147483647 - 1)
#endif

#endif /* MATLAB_TYPES_EXTENSION_H_ */
