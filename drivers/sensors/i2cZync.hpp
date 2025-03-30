#pragma once

#include <cstdint>
#include <string>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

namespace drivers::i2c {

class I2C_Zynq {
public:
    I2C_Zynq();
    ~I2C_Zynq();

    // Initialize I2C interface
    bool initialize(const std::string& device = "/dev/i2c-1", uint8_t default_address = 0x00);
    
    // Set slave device address
    bool setSlaveAddress(uint8_t address);
    
    // Basic read/write operations
    bool writeByte(uint8_t reg, uint8_t value);
    bool writeBytes(uint8_t reg, const uint8_t* values, uint16_t length);
    uint8_t readByte(uint8_t reg);
    bool readBytes(uint8_t reg, uint8_t* values, uint16_t length);
    
    // Combined write-then-read operation
    bool writeThenRead(uint8_t reg, uint8_t* writeData, uint16_t writeLength,
                      uint8_t* readData, uint16_t readLength);

private:
    int _i2cFile;               // File descriptor for I2C device
    uint8_t _currentAddress;    // Current slave address
    std::string _devicePath;    // Path to I2C device

    bool _checkDevice();
};

} // namespace drivers::i2c