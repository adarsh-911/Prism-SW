#pragma once
#include <cstdint>

namespace drivers::spi {

class SpiPsMio {
public:
    SpiPsMio();
    ~SpiPsMio();

    // Initialize SPI on PS-MIO pins
    bool initialize(uint32_t spiClockHz = 1000000); // Default: 1MHz

    // Transfer a single byte (full-duplex)
    uint8_t transferByte(uint8_t data);

    // Transfer multiple bytes (blocking)
    void transfer(const uint8_t* txData, uint8_t* rxData, uint16_t length);

    // Chip Select control
    void csAssert();
    void csDeassert();

    // Delays (µs)
    static void delayMicroseconds(uint32_t us);

private:
    // PS-MIO Pin Configuration (adjust based on your hardware)
    enum PsMioPins {
        MIO_SPI_CS   = 7,   // Example: MIO7 = CS
        MIO_SPI_MOSI = 8,    // Example: MIO8 = MOSI
        MIO_SPI_MISO = 9,    // Example: MIO9 = MISO
        MIO_SPI_SCK  = 10    // Example: MIO10 = SCK
    };

    bool _initialized = false;
    uint32_t _spiClockHz;
};

} // namespace drivers::spi