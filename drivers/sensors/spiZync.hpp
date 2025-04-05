#pragma once

#include <cstdint>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

namespace drivers::spi {

class SpiPsDev {
public:
    SpiPsDev();
    ~SpiPsDev();

    bool initialize(const std::string& device = "/dev/spidev0.0",
                    uint32_t speedHz = 1000000,
                    uint8_t mode = SPI_MODE_0,
                    uint8_t bitsPerWord = 8);

    bool transfer(const uint8_t* txData, uint8_t* rxData, uint16_t length);
    uint8_t transferByte(uint8_t byte);

private:
    int _spiFd;
    uint32_t _speedHz;
    uint8_t _mode;
    uint8_t _bitsPerWord;
};

} // namespace drivers::spi
