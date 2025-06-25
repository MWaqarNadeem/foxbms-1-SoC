#include "socEstimator.h"
#include "socEstimator_initialize.h"
#include "socEstimator_terminate.h"

void SOX_GetStateOfCharge_fromLSTM(float *voltage, float *current, float *temperature, int len, float *soc_out) {
    static int is_initialized = 0;
    if (!is_initialized) {
        socEstimator_initialize();
        is_initialized = 1;
    }

    // Allocate arrays and call estimator
    float soc_array[1024];  // adjust size as needed
    float step_times[1024]; // optional, remove if unused

    socEstimator(voltage, current, temperature, soc_array, step_times);

    *soc_out = soc_array[len - 1];  // take latest estimate
}
