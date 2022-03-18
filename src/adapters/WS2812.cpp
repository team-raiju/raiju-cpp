#include "utils.h"

#include "WS2812.hpp"

#define PWM_BIT_1 12
#define PWM_BIT_0 6

namespace raiju {

uint32_t Color::to_bits() const {
    uint32_t bits = 0;

    // Blue
    for (int8_t i = 7; i >= 0; i--) {
        if (B & (1 << i)) {
            bits |= (1 << (23 - (7 - i)));
        }
    }

    // Red
    for (int8_t i = 7; i >= 0; i--) {
        if (R & (1 << i)) {
            bits |= (1 << (15 - (7 - i)));
        }
    }

    // Green
    for (int8_t i = 7; i >= 0; i--) {
        if (G & (1 << i)) {
            bits |= (1 << (7 - (7 - i)));
        }
    }

    return bits;
}

WS2812::WS2812(PWM pwm, uint8_t led_amount) : pwm(pwm) {
    this->led_amount = min(led_amount, WS2812_MAX_LED_AMOUNT);

    reset_all();
    send();
}

void WS2812::reset_all() {
    for (uint8_t i = 0; i < led_amount; i++) {
        set_color(i, Color::black());
    }
}

void WS2812::set_color(uint8_t led_index, Color color) {
    if (led_index >= led_amount) {
        return;
    }

    led_data[led_index] = color.to_bits();
}

void WS2812::send() {
    for (uint8_t i = 0; i < led_amount; i++) {
        for (int8_t j = 23; j >= 0; j--) {
            if (led_data[i] & (1 << j)) {
                pwm_data[(i * 24) + j] = PWM_BIT_1;
            } else {
                pwm_data[(i * 24) + j] = PWM_BIT_0;
            }
        }
    }

    pwm.start_dma((uint32_t*)pwm_data, led_amount * 24);
}

} // namespace raiju

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == TIM2) {
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
    }
}
