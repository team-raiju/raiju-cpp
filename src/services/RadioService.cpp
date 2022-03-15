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
        map<uint16_t, int8_t>(ppms[0].constrained_value(), PPM::min_value_ms, PPM::max_value_ms, -100, 100),
        map<uint16_t, int8_t>(ppms[1].constrained_value(), PPM::min_value_ms, PPM::max_value_ms, -100, 100),
    };
}

} // namespace raiju
