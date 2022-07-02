#if defined(UART_RADIO) && defined(UART_DEBUG)
#error "Can't define both UART_RADIO and UART_DEBUG"
#endif

#if !defined(__RADIO_SERVICE_HPP__)
#define __RADIO_SERVICE_HPP__

#include <cstdint>

#include "PPM.hpp"
#include "Ticker.hpp"
#include "hal.hpp"

#define RXDATA_SIZE 25
#define CHANNELS 16

#define RX_RADIO_FIRST_BYTE 0x0F
#define RX_RADIO_LAST_BYTE  0x00
#define RX_RADIO_MIN_VALUE  0
#define RX_RADIO_MAX_VALUE  2047


#ifdef UART_RADIO
    #define CH4_LOW_THRESHOLD   768
    #define CH4_HIGH_THRESHOLD  1268
    #define CH3_LOW_THRESHOLD   768
    #define CH3_HIGH_THRESHOLD  1268

#else
    #define CH4_LOW_THRESHOLD   1250
    #define CH4_HIGH_THRESHOLD  1750
    #define CH3_LOW_THRESHOLD   1500
    #define CH3_HIGH_THRESHOLD  1800


#endif


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

    uint8_t rxdata[RXDATA_SIZE] = {0};
    uint16_t channels[CHANNELS] = {0};
    bool last_data_broken;

    Ticker last_sbus_packet;
#else
    PPM ppms[4];
#endif
};

} // namespace raiju

#endif // __RADIO_SERVICE_HPP__
