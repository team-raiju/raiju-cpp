#include <cstdint>

#include "main.h"

#include "inc/GPIO.hpp"

namespace hal {

GPIO::GPIO(GPIO_TypeDef *port, Pin pin) : _port(port), _pin(pin) {}

GPIO::Pin GPIO::pin() const {
    return this->_pin;
}

void GPIO::toggle() {
    HAL_GPIO_TogglePin(this->_port, this->_pin);
}

void GPIO::set() {
    HAL_GPIO_WritePin(this->_port, this->_pin, GPIO_PIN_SET);
}

void GPIO::reset() {
    HAL_GPIO_WritePin(this->_port, this->_pin, GPIO_PIN_RESET);
}

bool GPIO::is_active() {
    return HAL_GPIO_ReadPin(this->_port, this->_pin) == GPIO_PIN_SET;
}

} // namespace hal
