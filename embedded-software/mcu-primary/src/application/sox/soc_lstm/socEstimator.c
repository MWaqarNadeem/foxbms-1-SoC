/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: socEstimator.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

/* Include Files */
#include "socEstimator.h"
#include "predictAndUpdateState.h"
#include "resetState.h"
#include "socEstimator_data.h"
#include "socEstimator_emxutil.h"
#include "socEstimator_initialize.h"
#include "socEstimator_internal_types.h"
#include "socEstimator_types.h"

/* Variable Definitions */
static c_coder_internal_ctarget_DeepLe net;

static boolean_T net_not_empty;

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *voltage
 *                const emxArray_real_T *current
 *                const emxArray_real_T *temperature
 *                emxArray_real_T *soc
 * Return Type  : void
 */
void socEstimator(const emxArray_real_T *voltage,
                  const emxArray_real_T *current,
                  const emxArray_real_T *temperature, emxArray_real_T *soc)
{
  const double *current_data;
  const double *temperature_data;
  const double *voltage_data;
  double *soc_data;
  int i;
  int k;
  if (!isInitialized_socEstimator) {
    socEstimator_initialize();
  }
  temperature_data = temperature->data;
  current_data = current->data;
  voltage_data = voltage->data;
  if (!net_not_empty) {
    net.IsNetworkInitialized = false;
    net.matlabCodegenIsDeleted = false;
    net_not_empty = true;
    DeepLearningNetwork_resetState(&net);
  }
  /*  Preallocate outputs */
  i = soc->size[0] * soc->size[1];
  soc->size[0] = 1;
  soc->size[1] = voltage->size[1];
  emxEnsureCapacity_real_T(soc, i);
  soc_data = soc->data;
  /*  step_times = zeros(1, n); */
  i = voltage->size[1];
  for (k = 0; k < i; k++) {
    double b_voltage[3];
    float f;
    /*  tic; */
    b_voltage[0] = voltage_data[k];
    b_voltage[1] = current_data[k];
    b_voltage[2] = temperature_data[k];
    f = c_DeepLearningNetwork_predictAn(&net, b_voltage);
    soc_data[k] = f;
    /*  step_times(k) = toc; */
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void socEstimator_delete(void)
{
  if (!net.matlabCodegenIsDeleted) {
    net.matlabCodegenIsDeleted = true;
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void socEstimator_init(void)
{
  net_not_empty = false;
  net.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for socEstimator.c
 *
 * [EOF]
 */
