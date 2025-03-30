#include "spi_ps_mio.hpp"
#include <fcntl.h>      // open()
#include <unistd.h>     // close(), usleep()
#include <sys/ioctl.h>  // ioctl()
#include <linux/spi/spidev.h>
#include <cstring>

namespace drivers::spi {

SpiPsMio::SpiPsMio() {}

SpiPsMio::~SpiPsMio() {
    // Cleanup if needed
}

bool SpiPsMio::initialize(uint32_t spiClockHz) {
    /* TODO: Configure PS-MIO pins for SPI in Zynq-7020
     * Steps:
     * 1. Open `/dev/spidevX.Y` (X=bus, Y=CS)
     * 2. Set SPI mode (SPI_MODE_0)
     * 3. Set max speed (spiClockHz)
     * 4. Set MSB-first (SPI_LSB_FIRST = 0)
     * 5. Verify success
     */
    _spiClockHz = spiClockHz;
    _initialized = true;
    return true; // Change based on actual init
}

uint8_t SpiPsMio::transferByte(uint8_t data) {
    uint8_t rxData = 0;
    transfer(&data, &rxData, 1);
    return rxData;
}

void SpiPsMio::transfer(const uint8_t* txData, uint8_t* rxData, uint16_t length) {
    if (!_initialized) return;

    /* TODO: Implement SPI transfer
     * Steps:
     * 1. Assert CS (low)
     * 2. Wait ≥15 µs
     * 3. For each byte:
     *    a. Write MOSI, read MISO (MSB-first)
     *    b. Wait ≥10 µs between bytes
     * 4. Deassert CS (high)
     * 5. Wait ≥25 µs before next transaction
     */
}

void SpiPsMio::csAssert() {
    // Set CS low (active)
    delayMicroseconds(15); // Required delay
}

void SpiPsMio::csDeassert() {
    // Set CS high (inactive)
    delayMicroseconds(25); // Required delay
}

void SpiPsMio::delayMicroseconds(uint32_t us) {
    usleep(us); // Linux delay (replace with HW timer if needed)
}

} // 