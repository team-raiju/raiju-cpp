#if defined(UART_RADIO) && defined(UART_DEBUG)
#error "Can't define both UART_RADIO and UART_DEBUG"
#endif

#if !defined(__RADIO_SERVICE_HPP__)
#define __RADIO_SERVICE_HPP__

#include <cstdint>

#include "PPM.hpp"
#include "Ticker.hpp"
#include "hal.hpp"

#define RXDATA_SIZE 30
#define CHANNELS 16

namespace raiju {

class RadioService
#ifdef UART_RADIO
    : public hal::mcu::uart_interruptible
#endif
{
public:
    struct Coordinate {
        int8_t x, y;
    };

public:
    RadioService();

    Coordinate coordinates() const;

    uint16_t get_ch1() const;
    uint16_t get_ch2() const;
    uint16_t get_ch3() const;
    uint16_t get_ch4() const;

#ifdef UART_RADIO
    void on_interrupt(UART_HandleTypeDef* huart);
#endif

private:
#ifdef UART_RADIO
    hal::UART uart;

    uint8_t rxdata[RXDATA_SIZE];
    uint16_t channels[CHANNELS];

    Ticker last_sbus_packet;
#else
    PPM ppms[4];
#endif
};

} // namespace raiju

#endif // __RADIO_SERVICE_HPP__
