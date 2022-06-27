#if !defined(__BLUETOOTH_SERVICE_HPP__)
#define __BLUETOOTH_SERVICE_HPP__

#include <string>

#include "hal.hpp"

namespace raiju {

#define PACKET_SIZE 12

class BluetoothService : public hal::mcu::uart_interruptible {
public:
    union Packet {
        struct {
            uint8_t _header;
            uint8_t enabledDistanceSensors;
            uint8_t enabledLineSensors;
            uint8_t reverseSpeed;
            uint8_t reverseTimeMs;
            uint8_t turnSpeed;
            uint8_t turnTimeMs;
            uint8_t stepWaitTimeMs;
            uint8_t preStrategy;
            uint8_t strategy;
            uint8_t maxMotorSpeed;
            uint8_t _chk;
        };
        uint8_t _raw[PACKET_SIZE];

        bool is_data_request();
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
    uint8_t dma_data[PACKET_SIZE];
};

} // namespace raiju

#endif // __BLUETOOTH_SERVICE_HPP__
