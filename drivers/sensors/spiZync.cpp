#include "SpiPsDev.hpp"
#include <cstring>

namespace drivers::spi {

SpiPsDev::SpiPsDev()
    : _spiFd(-1), _speedHz(1000000), _mode(SPI_MODE_0), _bitsPerWord(8) {}

SpiPsDev::~SpiPsDev() {
    if (_spiFd >= 0) {
        close(_spiFd);
    }
}

bool SpiPsDev::initialize(const std::string& device,
                          uint32_t speedHz,
                          uint8_t mode,
                          uint8_t bitsPerWord) {
    _speedHz = speedHz;
    _mode = mode;
    _bitsPerWord = bitsPerWord;

    _spiFd = open(device.c_str(), O_RDWR);
    if (_spiFd < 0) return false;

    if (ioctl(_spiFd, SPI_IOC_WR_MODE, &_mode) < 0) return false;
    if (ioctl(_spiFd, SPI_IOC_WR_BITS_PER_WORD, &_bitsPerWord) < 0) return false;
    if (ioctl(_spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &_speedHz) < 0) return false;

    return true;
}

bool SpiPsDev::transfer(const uint8_t* txData, uint8_t* rxData, uint16_t length) {
    if (_spiFd < 0) return false;

    struct spi_ioc_transfer tr = {
        .tx_buf = reinterpret_cast<unsigned long>(txData),
        .rx_buf = reinterpret_cast<unsigned long>(rxData),
        .len = length,
        .delay_usecs = 0,
        .speed_hz = _speedHz,
        .bits_per_word = _bitsPerWord,
    };

    return ioctl(_spiFd, SPI_IOC_MESSAGE(1), &tr) >= 0;
}

uint8_t SpiPsDev::transferByte(uint8_t byte) {
    uint8_t rx = 0;
    transfer(&byte, &rx, 1);
    return rx;
}

} // namespace drivers::spi
