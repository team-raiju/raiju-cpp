#include <cstring>

// #include "utils.h"

#include "hal.hpp"

#include "BluetoothService.hpp"

namespace raiju {

BluetoothService::BluetoothService() : uart(&huart3) {
    hal::mcu::add_uart_interrupt(this);
    _data_available = false;

    uart.receive_dma(dma_data, sizeof(Packet));
}

void BluetoothService::transmit(uint8_t* data, size_t size) {
    uart.transmit(data, std::min<int>(size, 20));
}

void BluetoothService::transmit(std::string data) {
    uart.transmit((uint8_t*)data.data(), std::min<int>(data.length(), 20));
}

bool BluetoothService::data_available() {
    if (_data_available) {
        _data_available = false;
        return true;
    }

    return false;
}

BluetoothService::Packet BluetoothService::last_read_packet() {
    Packet p;
    memcpy(&p, dma_data, sizeof(Packet));
    return p;
}

void BluetoothService::on_interrupt(UART_HandleTypeDef* huart) {
    if (huart->Instance == uart.instance()) {
        uint8_t chk = 0;

        for (int i = 0; i < PACKET_SIZE - 1; i++) {
            chk ^= dma_data[i];
        }

        _data_available = chk == dma_data[PACKET_SIZE - 1];
    }
}

} // namespace raiju
