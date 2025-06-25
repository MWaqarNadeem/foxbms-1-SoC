/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_socEstimator_api.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

#ifndef _CODER_SOCESTIMATOR_API_H
#define _CODER_SOCESTIMATOR_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void socEstimator(emxArray_real_T *voltage, emxArray_real_T *current,
                  emxArray_real_T *temperature, emxArray_real_T *soc);

void socEstimator_api(const mxArray *const prhs[3], const mxArray **plhs);

void socEstimator_atexit(void);

void socEstimator_initialize(void);

void socEstimator_terminate(void);

void socEstimator_xil_shutdown(void);

void socEstimator_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_socEstimator_api.h
 *
 * [EOF]
 */
