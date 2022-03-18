#if !defined(__LED_SERVICE_HPP__)
#define __LED_SERVICE_HPP__

#include "WS2812.hpp"
#include "hal.hpp"

namespace raiju {

class LEDService {
public:
    LEDService();

    void toggle_board_led();
    void board_led_on();
    void board_led_off();

    void led_stripe_set(size_t idx, Color color);
    void led_stripe_reset();
    void led_stripe_send();

    void test();

private:
    WS2812 led_stripe;
    hal::GPIO led_board;
};

} // namespace raiju

#endif // __LED_SERVICE_HPP__
