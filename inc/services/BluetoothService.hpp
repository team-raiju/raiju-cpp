#if !defined(__BLUETOOTH_SERVICE_HPP__)
#define __BLUETOOTH_SERVICE_HPP__

#include <string>

#include "hal.hpp"

namespace raiju {

class BluetoothService : public hal::mcu::uart_interruptible {
public:
    struct Packet {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
    };

    BluetoothService();

    void transmit(uint8_t* data, size_t size);
    void transmit(std::string state);

    bool data_available();
    Packet last_read_packet();

    void on_interrupt(UART_HandleTypeDef* huart);

private:
    hal::UART uart;

    bool _data_available;
    uint8_t dma_data[3];
};

} // namespace raiju

#endif // __BLUETOOTH_SERVICE_HPP__
