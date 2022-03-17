#if !defined(__WS2812_HPP__)
#define __WS2812_HPP__

#include "hal.hpp"

#include "PWM.hpp"

#define WS2812_MAX_LED_AMOUNT 16

namespace raiju {

struct Color {
    uint8_t R, G, B;

    uint32_t to_bits() const;

    static Color black() {
        return Color{0x00, 0x00, 0x00};
    }

    static Color white() {
        return Color{0xFF, 0xFF, 0xFF};
    }
};

class WS2812 {
public:
    WS2812(PWM pwm, uint8_t led_amount);

    void reset_all();
    void set_color(uint8_t led_index, Color color);
    void send();

private:
    uint8_t led_amount;

    uint32_t led_data[WS2812_MAX_LED_AMOUNT];
    uint16_t pwm_data[WS2812_MAX_LED_AMOUNT * 24];

    PWM pwm;
};

} // namespace raiju

#endif // __WS2812_HPP__
