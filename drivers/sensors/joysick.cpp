#include "joystick.hpp"

namespace drivers::joystick {

Joystick::Joystick() {}

Joystick::~Joystick() {}

bool Joystick::initialize() {
    return _spi.initialize(1000000); // 1MHz SPI clock
}

void Joystick::getPosition(int8_t& x, int8_t& y) {
    uint8_t cmd = 0x00; // Standard packet request
    uint8_t response[5];
    sendCommand(cmd);
    readResponse(response, 5);

    uint16_t rawX = (response[1] << 8) | response[0];
    uint16_t rawY = (response[3] << 8) | response[2];
    x = static_cast<int8_t>((rawX / 1023.0f * 200) - 100);
    y = static_cast<int8_t>((rawY / 1023.0f * 200) - 100);
}

bool Joystick::getTriggerButton() {
    uint8_t cmd = 0x00;
    uint8_t response[5];
    sendCommand(cmd);
    readResponse(response, 5);
    return (response[4] & 0x02) != 0; // TRIGGER bit
}

bool Joystick::getJoystickButton() {
    uint8_t cmd = 0x00;
    uint8_t response[5];
    sendCommand(cmd);
    readResponse(response, 5);
    return (response[4] & 0x01) != 0; // JOYSTICK bit
}

void Joystick::setLedRGB(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t cmd = 0x84; // cmdSetLedRGB
    uint8_t params[4] = {red, green, blue, 0};
    sendCommand(cmd, params, 3);
}

void Joystick::sendCommand(uint8_t cmd, uint8_t* params, uint8_t paramCount) {
    _spi.csAssert();
    _spi.transferByte(cmd);
    for (uint8_t i = 0; i < paramCount; i++) {
        _spi.delayMicroseconds(10); // Inter-byte delay
        _spi.transferByte(params[i]);
    }
    _spi.csDeassert();
}

void Joystick::readResponse(uint8_t* buffer, uint8_t length) {
    _spi.csAssert();
    for (uint8_t i = 0; i < length; i++) {
        buffer[i] = _spi.transferByte(0x00); // Dummy write to read
        if (i < length - 1) _spi.delayMicroseconds(10);
    }
    _spi.csDeassert();
}

} // namespace drivers::joystick