// ========================================================================================
// LSM6DSL - Driver for STMicroelectronics LSM6DSL IMU (Gyroscope + Accelerometer)
// ----------------------------------------------------------------------------------------
// This class provides an abstraction layer for interfacing with the LSM6DSL sensor
// over I2C using the I2C_Zynq driver. It supports both raw data access and converted
// float values (in dps/g).
//
// Features:
// - Device initialization and identity check (WHO_AM_I)
// - Configuration of gyroscope and accelerometer:
//      * Data rate (ODR)
//      * Full-scale range
//      * Low power modes
// - Read raw or scaled gyroscope and accelerometer data on X, Y, and Z axes
//
// Usage:
// 1. Pass a reference to an initialized I2C_Zynq object to the constructor.
// 2. Call `init()` to check communication and prepare the sensor.
// 3. Use `configGyroscope()` and `configAccelerometer()` to set ODR and FS.
// 4. Use `readGyro()` / `readAccel()` for float readings,
//    or `readGyroRaw()` / `readAccelRaw()` for raw 16-bit integers.
//
// Example:
//     drivers::i2c::I2C_Zynq i2c;
//     i2c.initialize("/dev/i2c-1", LSM6DSL::I2C_ADDRESS);
//     drivers::gyro::LSM6DSL imu(i2c);
//     imu.init();
//     imu.configGyroscope(LSM6DSL::ODR_104_HZ, LSM6DSL::GYRO_FS_500);
//     imu.configAccelerometer(LSM6DSL::ODR_104_HZ, LSM6DSL::ACC_FS_4G);
//     float gx, gy, gz;
//     imu.readGyro(gx, gy, gz);
//
// Notes:
// - Sensitivities are internally calculated based on full-scale settings.
// - This driver assumes a little-endian host.
// - You may need to apply rotation or calibration depending on your hardware mounting.
//
// Author: Prajwal M
// ========================================================================================

#pragma once

#include <cstdint>
#include "i2cZync.hpp"

namespace drivers::gyro {

class LSM6DSL {
public:
    static constexpr uint8_t I2C_ADDRESS = 0x6A;

    static constexpr uint8_t WHO_AM_I      = 0x0F;
    static constexpr uint8_t CTRL1_XL      = 0x10;
    static constexpr uint8_t CTRL2_G       = 0x11;
    static constexpr uint8_t CTRL3_C       = 0x12;
    static constexpr uint8_t CTRL6_C       = 0x15;
    static constexpr uint8_t CTRL7_G       = 0x16;
    static constexpr uint8_t OUTX_L_G      = 0x22;
    static constexpr uint8_t OUTX_H_G      = 0x23;
    static constexpr uint8_t OUTY_L_G      = 0x24;
    static constexpr uint8_t OUTY_H_G      = 0x25;
    static constexpr uint8_t OUTZ_L_G      = 0x26;
    static constexpr uint8_t OUTZ_H_G      = 0x27;
    static constexpr uint8_t OUTX_L_XL     = 0x28;
    static constexpr uint8_t OUTX_H_XL     = 0x29;
    static constexpr uint8_t OUTY_L_XL     = 0x2A;
    static constexpr uint8_t OUTY_H_XL     = 0x2B;
    static constexpr uint8_t OUTZ_L_XL     = 0x2C;
    static constexpr uint8_t OUTZ_H_XL     = 0x2D;

    static constexpr uint8_t DEVICE_ID     = 0x6A;

    enum GyroFullScale {
        GYRO_FS_245  = 0x00,
        GYRO_FS_500  = 0x04,
        GYRO_FS_1000 = 0x08,
        GYRO_FS_2000 = 0x0C
    };

    enum AccFullScale {
        ACC_FS_2G  = 0x00,
        ACC_FS_4G  = 0x08,
        ACC_FS_8G  = 0x0C,
        ACC_FS_16G = 0x04
    };

    enum DataRate {
        ODR_POWER_DOWN = 0x00,
        ODR_12_5_HZ    = 0x10,
        ODR_26_HZ      = 0x20,
        ODR_52_HZ      = 0x30,
        ODR_104_HZ     = 0x40,
        ODR_208_HZ     = 0x50,
        ODR_416_HZ     = 0x60,
        ODR_833_HZ     = 0x70,
        ODR_1660_HZ    = 0x80,
        ODR_3330_HZ    = 0x90,
        ODR_6660_HZ    = 0xA0
    };

    explicit LSM6DSL(drivers::i2c::I2C_Zynq& i2c);

    bool init();
    uint8_t readId();

    void configGyroscope(DataRate dataRate, GyroFullScale fullScale);
    void configAccelerometer(DataRate dataRate, AccFullScale fullScale);
    
    void setGyroLowPower(bool enable);
    void setAccLowPower(bool enable);
    
    void readGyro(float &x, float &y, float &z);
    void readAccel(float &x, float &y, float &z);
    void readGyroRaw(int16_t &x, int16_t &y, int16_t &z);
    void readAccelRaw(int16_t &x, int16_t &y, int16_t &z);

private:
    drivers::i2c::I2C_Zynq& _i2c;
    
    GyroFullScale currentGyroFS;
    AccFullScale currentAccelFS;

    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);
    void readRegisters(uint8_t reg, uint8_t* data, uint8_t length);
    
    float getGyroSensitivity(GyroFullScale fs);
    float getAccelSensitivity(AccFullScale fs);
};

} // namespace drivers::gyro