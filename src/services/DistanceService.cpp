#include <cstdint>

#include "hal.hpp"

#include "DistanceService.hpp"

using hal::GPIO;

namespace raiju {

DistanceService::DistanceService()
    : sensors{
          GPIO(GPIOB, GPIO::Pin::p0),  GPIO(GPIOC, GPIO::Pin::p13), GPIO(GPIOC, GPIO::Pin::p14),
          GPIO(GPIOC, GPIO::Pin::p10), GPIO(GPIOC, GPIO::Pin::p11), GPIO(GPIOC, GPIO::Pin::p12),
          GPIO(GPIOD, GPIO::Pin::p2),  GPIO(GPIOB, GPIO::Pin::p4),  GPIO(GPIOB, GPIO::Pin::p5),
      } {}

bool DistanceService::is_reading(uint8_t sensor) {
    if (sensor < 1 || sensor > 9) {
        return false;
    }

    return !this->sensors[sensor - 1].is_active();
}

} // namespace raiju
