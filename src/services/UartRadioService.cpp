#ifdef UART_RADIO

#include "utils.h"

#include "RadioService.hpp"

namespace raiju {

RadioService::RadioService() : uart(&huart1) {
    hal::mcu::add_uart_interrupt(this);
    uart.receive_it(rxdata, RXDATA_SIZE);
}

RadioService::Coordinate RadioService::coordinates() const {
    // ??
    return Coordinate{ 0, 0 };
}

uint16_t RadioService::get_ch1() const {
    return channels[0];
}

uint16_t RadioService::get_ch2() const {
    return channels[0];
}

uint16_t RadioService::get_ch3() const {
    return channels[0];
}

uint16_t RadioService::get_ch4() const {
    return channels[0];
}

void RadioService::on_interrupt(UART_HandleTypeDef* huart) {
    if (huart->Instance != uart.instance()) {
        return;
    }

    last_sbus_packet.reset();

    channels[0] = ((rxdata[1] | rxdata[2] << 8) & 0x07FF);
    channels[1] = ((rxdata[2] >> 3 | rxdata[3] << 5) & 0x07FF);
    channels[2] = ((rxdata[3] >> 6 | rxdata[4] << 2 | rxdata[5] << 10) & 0x07FF);
    channels[3] = ((rxdata[5] >> 1 | rxdata[6] << 7) & 0x07FF);
    channels[4] = ((rxdata[6] >> 4 | rxdata[7] << 4) & 0x07FF);
    channels[5] = ((rxdata[7] >> 7 | rxdata[8] << 1 | rxdata[9] << 9) & 0x07FF);
    channels[6] = ((rxdata[9] >> 2 | rxdata[10] << 6) & 0x07FF);
    channels[7] = ((rxdata[10] >> 5 | rxdata[11] << 3) & 0x07FF); // & the other 8 + 2 channels if you need them
    channels[8] = ((rxdata[12] | rxdata[13] << 8) & 0x07FF);
    channels[9] = ((rxdata[13] >> 3 | rxdata[14] << 5) & 0x07FF);
    channels[10] = ((rxdata[14] >> 6 | rxdata[15] << 2 | rxdata[16] << 10) & 0x07FF);
    channels[11] = ((rxdata[16] >> 1 | rxdata[17] << 7) & 0x07FF);
    channels[12] = ((rxdata[17] >> 4 | rxdata[18] << 4) & 0x07FF);
    channels[13] = ((rxdata[18] >> 7 | rxdata[19] << 1 | rxdata[20] << 9) & 0x07FF);
    channels[14] = ((rxdata[20] >> 2 | rxdata[21] << 6) & 0x07FF);
    channels[15] = ((rxdata[21] >> 5 | rxdata[22] << 3) & 0x07FF);

    uart.receive_it(rxdata, RXDATA_SIZE);
}

} // namespace raiju

#endif
