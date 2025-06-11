#include "i2cZync.hpp"
#include <cstring>

namespace drivers::i2c {

I2C_Zynq::I2C_Zynq() : _i2cFile(-1), _currentAddress(0) {}

I2C_Zynq::~I2C_Zynq() {
    if (_i2cFile >= 0) {
        close(_i2cFile);
    }
}

bool I2C_Zynq::initialize(const std::string& device, uint8_t default_address) {
    _devicePath = device;
    _i2cFile = open(_devicePath.c_str(), O_RDWR);
    if (_i2cFile < 0) {
        return false;
    }
    return setSlaveAddress(default_address);
}

bool I2C_Zynq::setSlaveAddress(uint8_t address) {
    if (_i2cFile < 0) return false;
    if (ioctl(_i2cFile, I2C_SLAVE, address) < 0) {
        return false;
    }
    _currentAddress = address;
    return true;
}

bool I2C_Zynq::writeByte(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    return (write(_i2cFile, buffer, 2) == 2);
}

bool I2C_Zynq::writeBytes(uint8_t reg, const uint8_t* values, uint16_t length) {
    uint8_t* buffer = new uint8_t[length + 1];
    buffer[0] = reg;
    memcpy(buffer + 1, values, length);
    bool result = (write(_i2cFile, buffer, length + 1) == (length + 1));
    delete[] buffer;
    return result;
}

uint8_t I2C_Zynq::readByte(uint8_t reg) {
    uint8_t value = 0;
    if (write(_i2cFile, &reg, 1) != 1) {
        return 0;
    }
    if (read(_i2cFile, &value, 1) != 1) {
        return 0;
    }
    return value;
}

bool I2C_Zynq::readBytes(uint8_t reg, uint8_t* values, uint16_t length) {
    if (write(_i2cFile, &reg, 1) != 1) {
        return false;
    }
    return (read(_i2cFile, values, length) == length);
}

bool I2C_Zynq::writeThenRead(uint8_t reg, uint8_t* writeData, uint16_t writeLength,
                            uint8_t* readData, uint16_t readLength) {
    struct i2c_msg messages[2];
    struct i2c_rdwr_ioctl_data packet;
    messages[0].addr = _currentAddress;
    messages[0].flags = 0;
    messages[0].len = writeLength + 1;
    uint8_t* writeBuffer = new uint8_t[writeLength + 1];
    writeBuffer[0] = reg;
    memcpy(writeBuffer + 1, writeData, writeLength);
    messages[0].buf = writeBuffer;
    messages[1].addr = _currentAddress;
    messages[1].flags = I2C_M_RD;
    messages[1].len = readLength;
    messages[1].buf = readData;
    packet.msgs = messages;
    packet.nmsgs = 2;
    bool result = (ioctl(_i2cFile, I2C_RDWR, &packet) >= 0);
    delete[] writeBuffer;
    return result;
}

bool I2C_Zynq::_checkDevice() {
    if (_i2cFile < 0) return false;
    uint8_t dummy;
    return (read(_i2cFile, &dummy, 1) == 1);
}

} // namespace drivers::i2c