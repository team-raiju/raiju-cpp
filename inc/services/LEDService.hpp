#if !defined(__LED_SERVICE_HPP__)
#define __LED_SERVICE_HPP__

#include "WS2812.hpp"
#include "hal.hpp"

namespace raiju {

class LEDService {
public:
    LEDService();

    void toggle_board_led();

private:
    WS2812 led_stripe;
    hal::GPIO led_board;
};

} // namespace raiju

#endif // __LED_SERVICE_HPP__
