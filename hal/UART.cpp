#include "main.h"

#include "inc/UART.hpp"

namespace hal {

UART::UART(UART_HandleTypeDef* huart) : huart(huart) {}

void UART::transmit(uint8_t byte, uint32_t timeout) {
    HAL_UART_Transmit(huart, &byte, 1, timeout);
}

void UART::transmit(uint8_t* data, size_t size, uint32_t timeout) {
    HAL_UART_Transmit(huart, data, size, timeout);
}

void UART::receive_dma(uint8_t* data, size_t size) {
    HAL_UART_Receive_DMA(huart, data, size);
}

void UART::stop_dma() {
    HAL_UART_DMAStop(huart);
}

USART_TypeDef* UART::instance() const {
    return huart->Instance;
}

} // namespace hal
