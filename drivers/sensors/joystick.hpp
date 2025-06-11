/* =========================================================================
 * Joystick - SPI-based Joystick Driver (for PetaLinux + Zynq)
 * =========================================================================
 *
 * Overview:
 * ---------
 * - High-level driver for an SPI-controlled joystick module.
 * - Uses software SPI (SpiPsMio) for communication.
 * - Supports reading position, buttons, and controlling RGB LEDs.
 *
 * Functions:
 * ----------
 * - initialize(): Sets up the SPI interface.
 * - getPosition(x, y): Reads joystick X/Y axis as signed 8-bit values.
 * - getTriggerButton(): Reads the trigger button state.
 * - getJoystickButton(): Reads the joystick (center) button state.
 * - setLedRGB(r, g, b): Controls RGB LED on the joystick module.
 *
 * Internals:
 * ----------
 * - Uses sendCommand() to write commands to the joystick.
 * - Uses readResponse() to read back data.
 *
 * Requirements:
 * -------------
 * - Connected via SPI (handled by SpiPsMio).
 * - Ensure GPIO lines for SPI are properly configured via Device Tree.
 * - Suitable for use on Zynq platforms running PetaLinux.
 *
 * Example:
 * --------
 *   Joystick js;
 *   js.initialize();
 *   int8_t x, y;
 *   js.getPosition(x, y);
 *   bool pressed = js.getTriggerButton();
 *   js.setLedRGB(255, 0, 0); // Red LED
 * ========================================================================= */

#pragma once
#include "spiZync.hpp"
#include <cstdint>

namespace drivers::joystick {

class Joystick {
public:
    Joystick();
    ~Joystick();

    bool initialize();
    void getPosition(int8_t& x, int8_t& y);
    bool getTriggerButton();
    bool getJoystickButton();
    void setLedRGB(uint8_t red, uint8_t green, uint8_t blue);

private:
    drivers::spi::SpiPsDev _spi;
    void sendCommand(uint8_t cmd, uint8_t* params = nullptr, uint8_t paramCount = 0);
    void readResponse(uint8_t* buffer, uint8_t length);
};

} // namespace drivers::joystick