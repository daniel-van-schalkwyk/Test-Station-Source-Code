#ifndef temp_cal_coefs_h
#define temp_cal_coefs_h

#include <temp_sensor_address_reg.h>

/*  The following matrices are used for the different temperature sensor calibration
    A linear calibration is implemented with the following equation:
        T_cal = a1 * T_meas + a0
    The first number of each element in the matrix below is a1 and the second is a0.
*/

double tempCalCoefs[10][9][2] =  
                {
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                    {{1,2}, {1,2}, {1,2}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}, {2,1}},
                };

// Define variables for thermistor circuit and code
struct paramsThermistorNTC
{
  double voltDividerR;
  double thermistorResistance;
  double a2;
  double b2;
  double c2;
};
paramsThermistorNTC geyserWiseThermistorMain, geyserWiseThermistorPre;
#endif