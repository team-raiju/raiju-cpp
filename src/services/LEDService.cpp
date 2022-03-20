#include "LEDService.hpp"

namespace raiju {

LEDService::LEDService()
    : led_stripe(PWM(hal::TIM(&htim2), hal::TIM::Channel::ch1, false), 16), led_board(GPIOB, hal::GPIO::Pin::p1) {}

void LEDService::toggle_board_led() {
    led_board.toggle();
};

void LEDService::board_led_on() {
    led_board.set();
};

void LEDService::board_led_off() {
    led_board.reset();
};

void LEDService::led_stripe_set(size_t idx, Color color) {
    led_stripe.set_color(idx, color);
}

void LEDService::led_stripe_reset() {
    led_stripe.reset_all();
}

void LEDService::led_stripe_send() {
    led_stripe.send();
    hal::mcu::sleep(100);
}

void LEDService::purple_charge() {
    for (int i = 0; i < 16; i++) {
        led_stripe.set_color(i, Color::purple());
        led_stripe.send();

        hal::mcu::sleep(100);
    }
    
}

} // namespace raiju
