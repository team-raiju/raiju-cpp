#include "LEDService.hpp"

namespace raiju {

LEDService::LEDService()
    : led_stripe(PWM(hal::TIM(&htim2), hal::TIM::Channel::ch1, false), 16), led_board(GPIOB, hal::GPIO::Pin::p1) {}

void LEDService::toggle_board_led() {
    led_board.toggle();
};

} // namespace raiju
