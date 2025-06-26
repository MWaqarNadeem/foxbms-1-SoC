/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rtwtypes.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

#ifndef RTWTYPES_H
#define RTWTYPES_H

/*=======================================================================*
 * Fixed width word size data types:                                     *
 *   int64_T                      - signed 64 bit integers               *
 *   uint64_T                     - unsigned 64 bit integers             *
 *=======================================================================*/

#if defined(__APPLE__)
#ifndef INT64_T
#define INT64_T long
#define FMT64 "l"
#if defined(__LP64__) && !defined(INT_TYPE_64_IS_LONG)
#define INT_TYPE_64_IS_LONG
#endif
#endif
#endif

#if defined(__APPLE__)
#ifndef UINT64_T
#define UINT64_T unsigned long
#define FMT64 "l"
#if defined(__LP64__) && !defined(INT_TYPE_64_IS_LONG)
#define INT_TYPE_64_IS_LONG
#endif
#endif
#endif

/* Include Files */
//#include "tmwtypes.h"
#ifndef TMWTYPES_DEFINED
#define TMWTYPES_DEFINED

typedef signed char         int8_T;
typedef unsigned char       uint8_T;
typedef short               int16_T;
typedef unsigned short      uint16_T;
//typedef int                 int32_T;
typedef unsigned int        uint32_T;
typedef float               real32_T;
typedef double              real64_T;

typedef int                 boolean_T;

// Define true and false if not already defined
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

// Define 32-bit integer limits
#ifndef MAX_int32_T
#define MAX_int32_T 2147483647
#endif

#ifndef MIN_int32_T
#define MIN_int32_T (-2147483647 - 1)
#endif

#ifndef real32_T
typedef float real32_T;
#endif

#ifndef real64_T
typedef double real64_T;
#endif
/* 
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
#endif */

#ifndef boolean_T
typedef int boolean_T;
#endif


#ifndef MAX_int32_T
#define MAX_int32_T 2147483647
#endif

#ifndef MIN_int32_T
#define MIN_int32_T (-2147483647 - 1)
#endif

#endif 

/* TMWTYPES_DEFINED */


#endif
/*
 * File trailer for rtwtypes.h
 *
 * [EOF]
 */
