/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: socEstimator_initialize.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

/* Include Files */
#include "socEstimator_initialize.h"
#include "socEstimator.h"
#include "socEstimator_data.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void socEstimator_initialize(void)
{
  socEstimator_init();
  isInitialized_socEstimator = true;
}

/*
 * File trailer for socEstimator_initialize.c
 *
 * [EOF]
 */
