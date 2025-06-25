/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: resetState.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

/* Include Files */
#include "resetState.h"
#include "socEstimator_internal_types.h"

/* Function Definitions */
/*
 * Arguments    : c_coder_internal_ctarget_DeepLe *obj
 * Return Type  : void
 */
void DeepLearningNetwork_resetState(c_coder_internal_ctarget_DeepLe *obj)
{
  int k;
  for (k = 0; k < 10; k++) {
    obj->NetworkState[0].f1[0].f1[k] = 0.0F;
    obj->NetworkState[0].f1[1].f1[k] = 0.0F;
  }
}

/*
 * File trailer for resetState.c
 *
 * [EOF]
 */
