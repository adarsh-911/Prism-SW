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
    drivers::spi::SpiPsMio _spi;
    void sendCommand(uint8_t cmd, uint8_t* params = nullptr, uint8_t paramCount = 0);
    void readResponse(uint8_t* buffer, uint8_t length);
};

} // namespace drivers::joystick