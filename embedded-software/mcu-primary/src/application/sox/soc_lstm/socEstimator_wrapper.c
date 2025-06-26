#include "socEstimator.h"
#include "socEstimator_initialize.h"
#include "socEstimator_terminate.h"
#include "socEstimator_emxAPI.h"
#include "socEstimator_emxutil.h"

void SOX_GetStateOfCharge_fromLSTM(double *voltage, double *current, double *temperature, int len, double *soc_out) {
    static int is_initialized = 0;
    if (!is_initialized) {
        socEstimator_initialize();
        is_initialized = 1;
    }

    // Allocate arrays and call estimator
    // float soc_array[1024];  // adjust size as needed
    // float step_times[1024]; // optional, remove if unused

    emxArray_real_T *v_arr   = emxCreateWrapper_real_T(voltage, 1, len);
    emxArray_real_T *c_arr   = emxCreateWrapper_real_T(current, 1, len);
    emxArray_real_T *t_arr   = emxCreateWrapper_real_T(temperature, 1, len);
    emxArray_real_T *soc_arr = emxCreate_real_T(1, len);  // output

    socEstimator(v_arr, c_arr, t_arr, soc_arr);
    //socEstimator(voltage, current, temperature, soc_array);

    //*soc_out = soc_array[len - 1];  // take latest estimate
    *soc_out = soc_arr->data[len - 1];

    // Free arrays
    emxDestroyArray_real_T(v_arr);
    emxDestroyArray_real_T(c_arr);
    emxDestroyArray_real_T(t_arr);
    emxDestroyArray_real_T(soc_arr);
}
