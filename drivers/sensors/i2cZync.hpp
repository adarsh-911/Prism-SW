// ========================================================================================
// I2C_Zynq - I2C Communication Driver for Zynq-based Linux Systems
// ----------------------------------------------------------------------------------------
// This class provides a simple C++ interface for I2C communication on Zynq platforms
// running a Linux OS. It uses standard Linux I2C interfaces through the i2c-dev module.
//
// Features:
// - Open and initialize I2C device files
// - Set slave addresses dynamically
// - Perform register-based read and write operations
// - Support for combined write-then-read operations (e.g. for reading sensor data)
//
// Usage:
// 1. Create an instance of I2C_Zynq.
// 2. Call `initialize()` to open the I2C device.
// 3. Use `setSlaveAddress()` to specify the target slave address.
// 4. Use `writeByte()`, `writeBytes()`, `readByte()`, `readBytes()`, or `writeThenRead()`
//    for I2C communication.
//
// Example:
//     I2C_Zynq i2c;
//     if (i2c.initialize("/dev/i2c-1", 0x40)) {
//         i2c.writeByte(0x00, 0xFF);
//         uint8_t value = i2c.readByte(0x01);
//     }
//
// Notes:
// - Always check return values for error handling.
// - Ensure your application has permission to access /dev/i2c-*.
//
// Author: Prajwal M
// ========================================================================================

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

    bool initialize(const std::string& device = "/dev/i2c-1", uint8_t default_address = 0x00);
    bool setSlaveAddress(uint8_t address);
    
    bool writeByte(uint8_t reg, uint8_t value);
    bool writeBytes(uint8_t reg, const uint8_t* values, uint16_t length);
    uint8_t readByte(uint8_t reg);
    bool readBytes(uint8_t reg, uint8_t* values, uint16_t length);
    bool writeThenRead(uint8_t reg, uint8_t* writeData, uint16_t writeLength,
                      uint8_t* readData, uint16_t readLength);

private:
    int _i2cFile;
    uint8_t _currentAddress;
    std::string _devicePath;
    bool _checkDevice();
};

} // namespace drivers::i2c