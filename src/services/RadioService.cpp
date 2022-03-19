#include "utils.h"

#include "RadioService.hpp"

using hal::GPIO, hal::TIM;

namespace raiju {

RadioService::RadioService()
    : ppms{
          PPM(GPIO(GPIOC, GPIO::Pin::p6), TIM(&htim7)),
          PPM(GPIO(GPIOC, GPIO::Pin::p7), TIM(&htim7)),
          PPM(GPIO(GPIOC, GPIO::Pin::p8), TIM(&htim7)),
          PPM(GPIO(GPIOC, GPIO::Pin::p9), TIM(&htim7)),
      } {}

RadioService::Coordinate RadioService::coordinates() const {
    return Coordinate{
        map<int16_t, int8_t>(ppms[0].constrained_value(), PPM::min_value_ms, PPM::max_value_ms, -100, 100),
        map<int16_t, int8_t>(ppms[1].constrained_value(), PPM::min_value_ms, PPM::max_value_ms, -100, 100),
    };
}

uint16_t RadioService::get_ch1() const {
    return ppms[0].constrained_value();
}

uint16_t RadioService::get_ch2() const {
    return ppms[1].constrained_value();
}

uint16_t RadioService::get_ch3() const {
    return ppms[2].constrained_value();
}

uint16_t RadioService::get_ch4() const {
    return ppms[3].constrained_value();
}

} // namespace raiju
