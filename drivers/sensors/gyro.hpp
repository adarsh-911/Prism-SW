#pragma once

#include <cstdint>
#include "i2cZync.hpp"  // Include our I2C driver

namespace drivers::gyro {

class LSM6DSL {
public:
    // I2C address (low)
    static constexpr uint8_t I2C_ADDRESS = 0x6A;

    // Register addresses (unchanged from your original)
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

    // Device ID value
    static constexpr uint8_t DEVICE_ID     = 0x6A;

    // Gyroscope full-scale selection (unchanged)
    enum GyroFullScale {
        GYRO_FS_245  = 0x00,
        GYRO_FS_500  = 0x04,
        GYRO_FS_1000 = 0x08,
        GYRO_FS_2000 = 0x0C
    };

    // Accelerometer full-scale selection (unchanged)
    enum AccFullScale {
        ACC_FS_2G  = 0x00,
        ACC_FS_4G  = 0x08,
        ACC_FS_8G  = 0x0C,
        ACC_FS_16G = 0x04
    };

    // Output data rate (unchanged)
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

    // Constructor now takes I2C interface reference
    explicit LSM6DSL(drivers::i2c::I2C_Zynq& i2c);

    // Initialization
    bool init();
    uint8_t readId();

    // Configuration
    void configGyroscope(DataRate dataRate, GyroFullScale fullScale);
    void configAccelerometer(DataRate dataRate, AccFullScale fullScale);
    
    // Low power mode
    void setGyroLowPower(bool enable);
    void setAccLowPower(bool enable);
    
    // Read sensor data
    void readGyro(float &x, float &y, float &z);
    void readAccel(float &x, float &y, float &z);
    void readGyroRaw(int16_t &x, int16_t &y, int16_t &z);
    void readAccelRaw(int16_t &x, int16_t &y, int16_t &z);

private:
    drivers::i2c::I2C_Zynq& _i2c;  // Reference to I2C driver
    
    // Current configuration
    GyroFullScale currentGyroFS;
    AccFullScale currentAccelFS;

    // Private helper methods
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);
    void readRegisters(uint8_t reg, uint8_t* data, uint8_t length);
    
    float getGyroSensitivity(GyroFullScale fs);
    float getAccelSensitivity(AccFullScale fs);
};

} // namespace drivers::gyro