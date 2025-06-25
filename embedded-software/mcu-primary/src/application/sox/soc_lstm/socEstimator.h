/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: socEstimator.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

#ifndef SOCESTIMATOR_H
#define SOCESTIMATOR_H

/* Include Files */
#include "rtwtypes.h"
#include "socEstimator_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void socEstimator(const emxArray_real_T *voltage,
                         const emxArray_real_T *current,
                         const emxArray_real_T *temperature,
                         emxArray_real_T *soc);

void socEstimator_delete(void);

void socEstimator_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for socEstimator.h
 *
 * [EOF]
 */
