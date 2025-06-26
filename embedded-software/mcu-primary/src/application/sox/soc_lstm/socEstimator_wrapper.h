#ifndef SOC_ESTIMATOR_WRAPPER_H
#define SOC_ESTIMATOR_WRAPPER_H

void SOX_GetStateOfCharge_fromLSTM(double *voltage, double *current, double *temperature, int len, double *soc_out);

#endif
