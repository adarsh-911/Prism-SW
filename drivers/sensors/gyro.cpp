#include "gyro.hpp"
#include <chrono>
#include <thread>

namespace drivers::gyro {

LSM6DSL::LSM6DSL(drivers::i2c::I2C_Zynq& i2c) : 
    _i2c(i2c),
    currentGyroFS(GYRO_FS_245),
    currentAccelFS(ACC_FS_2G) {
}

bool LSM6DSL::init() {
    if (!_i2c.setSlaveAddress(I2C_ADDRESS)) {
        return false;
    }

    uint8_t id = readId();
    if (id != DEVICE_ID) {
        return false;
    }
    
    writeRegister(CTRL3_C, 0x01);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
    writeRegister(CTRL3_C, 0x44);
    
    configGyroscope(ODR_104_HZ, GYRO_FS_245);
    configAccelerometer(ODR_104_HZ, ACC_FS_2G);
    
    return true;
}

uint8_t LSM6DSL::readId() {
    return readRegister(WHO_AM_I);
}

void LSM6DSL::configGyroscope(DataRate dataRate, GyroFullScale fullScale) {
    uint8_t ctrl = dataRate | fullScale;
    writeRegister(CTRL2_G, ctrl);
    currentGyroFS = fullScale;
}

void LSM6DSL::configAccelerometer(DataRate dataRate, AccFullScale fullScale) {
    uint8_t ctrl = dataRate | fullScale;
    writeRegister(CTRL1_XL, ctrl);
    currentAccelFS = fullScale;
}

void LSM6DSL::setGyroLowPower(bool enable) {
    uint8_t ctrl = readRegister(CTRL7_G);
    ctrl &= ~(0x80);
    if (enable) {
        ctrl |= 0x80;
    }
    writeRegister(CTRL7_G, ctrl);
}

void LSM6DSL::setAccLowPower(bool enable) {
    uint8_t ctrl = readRegister(CTRL6_C);
    ctrl &= ~(0x10);
    if (enable) {
        ctrl |= 0x10;
    }
    writeRegister(CTRL6_C, ctrl);
}

void LSM6DSL::readGyro(float &x, float &y, float &z) {
    int16_t rawX, rawY, rawZ;
    readGyroRaw(rawX, rawY, rawZ);
    
    float sensitivity = getGyroSensitivity(currentGyroFS);
    
    x = rawX * sensitivity;
    y = rawY * sensitivity;
    z = rawZ * sensitivity;
}

void LSM6DSL::readAccel(float &x, float &y, float &z) {
    int16_t rawX, rawY, rawZ;
    readAccelRaw(rawX, rawY, rawZ);
    
    float sensitivity = getAccelSensitivity(currentAccelFS);
    
    x = rawX * sensitivity;
    y = rawY * sensitivity;
    z = rawZ * sensitivity;
}

void LSM6DSL::readGyroRaw(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t buffer[6];
    readRegisters(OUTX_L_G, buffer, 6);
    
    x = (int16_t)(buffer[1] << 8 | buffer[0]);
    y = (int16_t)(buffer[3] << 8 | buffer[2]);
    z = (int16_t)(buffer[5] << 8 | buffer[4]);
}

void LSM6DSL::readAccelRaw(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t buffer[6];
    readRegisters(OUTX_L_XL, buffer, 6);
    
    x = (int16_t)(buffer[1] << 8 | buffer[0]);
    y = (int16_t)(buffer[3] << 8 | buffer[2]);
    z = (int16_t)(buffer[5] << 8 | buffer[4]);
}

float LSM6DSL::getGyroSensitivity(GyroFullScale fs) {
    switch (fs) {
        case GYRO_FS_245: return 0.00875f;
        case GYRO_FS_500: return 0.0175f;
        case GYRO_FS_1000: return 0.035f;
        case GYRO_FS_2000: return 0.07f;
        default: return 0.00875f;
    }
}

float LSM6DSL::getAccelSensitivity(AccFullScale fs) {
    switch (fs) {
        case ACC_FS_2G: return 0.000061f;
        case ACC_FS_4G: return 0.000122f;
        case ACC_FS_8G: return 0.000244f;
        case ACC_FS_16G: return 0.000488f;
        default: return 0.000061f;
    }
}

uint8_t LSM6DSL::readRegister(uint8_t reg) {
    return _i2c.readByte(reg);
}

void LSM6DSL::writeRegister(uint8_t reg, uint8_t value) {
    _i2c.writeByte(reg, value);
}

void LSM6DSL::readRegisters(uint8_t reg, uint8_t* data, uint8_t length) {
    _i2c.readBytes(reg, data, length);
}

} // namespace drivers::gyro