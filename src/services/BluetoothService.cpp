#include <cstring>

// #include "utils.h"

#include "hal.hpp"

#include "BluetoothService.hpp"

namespace raiju {

bool BluetoothService::Packet::is_data_request() {
    return _raw[0] == 0xFE && _raw[1] == 0xFE;
}

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
    if (huart->Instance != uart.instance()) {
        return;
    }

    // Request config mode
    if (dma_data[0] == 0xFE && dma_data[1] == 0xFE) {
        _data_available = true;
        return;
    }

    // Header should always be 0xFF
    if (dma_data[0] != 0xFF) {
        _data_available = false;

        // Faulty packet, reset dma
        uart.stop_dma();
        memset(dma_data, 0, PACKET_SIZE);
        uart.receive_dma(dma_data, sizeof(Packet));
        return;
    }

    uint8_t chk = 0;

    for (int i = 0; i < PACKET_SIZE - 1; i++) {
        chk ^= dma_data[i];
    }

    if (chk == dma_data[PACKET_SIZE - 1]) {
        _data_available = true;
        return;
    }

    // Faulty packet, reset dma
    uart.stop_dma();
    memset(dma_data, 0, PACKET_SIZE);
    uart.receive_dma(dma_data, sizeof(Packet));
}

} // namespace raiju
