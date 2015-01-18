/** @file
Header file for HMC5883L three-axis magnetometer primary interface to Arduino over I2C.

This code is released under a Creative Commons Attribution 4.0 International license 
([CC-BY 4.0](https://creativecommons.org/licenses/by/4.0/)).

@author Paul J. Ganssle
@version 0.1
@date 2015-01-14
*/

#ifndef HMC5883L_H
#define HMC5883L_H

#include <Arduino.h>
#include <I2CDev.h>
#include <Vec3.h>
#include <Wire.h>

// Device addresses
#define HMC5883L_ADDR 0x1E

#define ConfigRegisterA 0x00
#define ConfigRegisterB 0x01
#define ModeRegister 0x02

#define DataRegister 0x03
#define StatusRegister 0x09

// Bias fields in mG
#define HMC_BIAS_XY 1160.0
#define HMC_BIAS_Z 1080.0

// Gain settings
#define HMC_GAIN088 0
#define HMC_GAIN130 1
#define HMC_GAIN190 2
#define HMC_GAIN250 3
#define HMC_GAIN400 4
#define HMC_GAIN470 5
#define HMC_GAIN560 6
#define HMC_GAIN810 7

// Measurement modes
#define HMC_AVG1 0
#define HMC_AVG2 1
#define HMC_AVG4 2
#define HMC_AVG8 3

// Output rates
#define HMC_RATE0075 0
#define HMC_RATE0150 1
#define HMC_RATE0300 2
#define HMC_RATE0750 3
#define HMC_RATE1500 4
#define HMC_RATE3000 5
#define HMC_RATE7500 6

// Measurement modes
#define HMC_MeasurementContinuous 0
#define HMC_MeasurementSingle 1
#define HMC_MeasurementIdle 2

// Bias modes
#define HMC_BIAS_NONE 0
#define HMC_BIAS_POSITIVE 1
#define HMC_BIAS_NEGATIVE 2

// Error codes
#define EC_BAD_GAIN_LEVEL 8
#define EC_INVALID_NAVG 9
#define EC_INVALID_OUTRATE 10
#define EC_INVALID_MEASUREMENT_MODE 11
#define EC_INVALID_BIAS_MODE 12

// Warning codes
#define WC_X_SATURATED 1
#define WC_Y_SATURATED 2
#define WC_Z_SATURATED 4


class HMC5883L {
public:
    HMC5883L();

    uint8_t initialize(bool noConfig=false);

    Vec3<int> readRawValues(void);
    Vec3<float> readScaledValues(void);
    Vec3<float> readCalibratedValues(void);

    Vec3<float> getCalibration(bool update);

    Vec3<float> runPosTest(void);
    Vec3<float> runNegTest(void);

    uint8_t getStatus(bool &isLocked, bool &isReady);

    uint8_t setGain(uint8_t gain_level);
    uint8_t setAveragingRate(uint8_t avg_rate);
    uint8_t setOutputRate(uint8_t out_rate);
    uint8_t setMeasurementMode(uint8_t mode);
    uint8_t setBiasMode(uint8_t mode);
    uint8_t setHighSpeedI2CMode(bool enabled);

    uint8_t getGain(bool updateCache=false);
    uint8_t getAveragingRate(bool updateCache=false);
    uint8_t getOutputRate(bool updateCache=false);
    uint8_t getMeasurementMode(bool updateCache=false);
    uint8_t getBiasMode(bool updateCache=false);

    uint8_t get_error_code(void);

    static const float outputRates[7] = [0.75, 1.50, 3.00, 7.50, 15.00, 30.00, 75.00];
    static const float gainRanges[8] = [0.88, 1.30, 1.90, 2.50, 4.00, 4.70, 5.60, 8.10];
    
private:
    I2CDev I2CDevice;
    Vec3<float> calibration;

    uint8_t gain;
    uint8_t averagingRate;
    uint8_t outputRate;
    uint8_t measurementMode;
    uint8_t biasMode;

    static const float gainValues[8] = [0.73, 0.92, 1.22, 1.52, 2.27, 2.56, 3.03, 4.35];
};

#endif