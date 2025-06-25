/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: socEstimator_terminate.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

/* Include Files */
#include "socEstimator_terminate.h"
#include "socEstimator.h"
#include "socEstimator_data.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void socEstimator_terminate(void)
{
  socEstimator_delete();
  isInitialized_socEstimator = false;
}

/*
 * File trailer for socEstimator_terminate.c
 *
 * [EOF]
 */
