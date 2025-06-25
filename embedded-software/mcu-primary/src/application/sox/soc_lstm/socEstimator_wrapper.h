#ifndef SOC_ESTIMATOR_WRAPPER_H
#define SOC_ESTIMATOR_WRAPPER_H

void SOX_GetStateOfCharge_fromLSTM(float *voltage, float *current, float *temperature, int len, float *soc_out);

#endif
