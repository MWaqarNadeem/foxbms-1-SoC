/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: socEstimator_internal_types.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

#ifndef SOCESTIMATOR_INTERNAL_TYPES_H
#define SOCESTIMATOR_INTERNAL_TYPES_H

/* Include Files */
#include "rtwtypes.h"
#include "socEstimator_types.h"

/* Type Definitions */
#ifndef typedef_cell_wrap_3
#define typedef_cell_wrap_3
typedef struct {
  float f1[10];
} cell_wrap_3;
#endif /* typedef_cell_wrap_3 */

#ifndef typedef_cell_wrap_4
#define typedef_cell_wrap_4
typedef struct {
  cell_wrap_3 f1[2];
} cell_wrap_4;
#endif /* typedef_cell_wrap_4 */

#ifndef typedef_c_coder_internal_ctarget_DeepLe
#define typedef_c_coder_internal_ctarget_DeepLe
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  cell_wrap_4 NetworkState[1];
  boolean_T IsNetworkInitialized;
} c_coder_internal_ctarget_DeepLe;
#endif /* typedef_c_coder_internal_ctarget_DeepLe */

#endif
/*
 * File trailer for socEstimator_internal_types.h
 *
 * [EOF]
 */
