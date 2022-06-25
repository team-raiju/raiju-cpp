#include <cstdint>

#include "config.hpp"
#include "hal.hpp"

#include "DistanceService.hpp"

using hal::GPIO;

namespace raiju {

// This must match src/app/ui/tabs/config-tab/config-tab.page.ts in the app
const uint8_t DistanceService::configMask[] = {
    0,      // none
    0,      // none
    0,      // none
    0,      // none
    1 << 3, // RIGHT
    1 << 4, // BRIGHT
    1 << 2, // FRONT
    1 << 0, // BLEFT
    1 << 1, // LEFT
};

DistanceService::DistanceService()
    : sensors{
          GPIO(GPIOB, GPIO::Pin::p0),  GPIO(GPIOC, GPIO::Pin::p13), GPIO(GPIOC, GPIO::Pin::p14),
          GPIO(GPIOC, GPIO::Pin::p10), GPIO(GPIOC, GPIO::Pin::p11), GPIO(GPIOC, GPIO::Pin::p12),
          GPIO(GPIOD, GPIO::Pin::p2),  GPIO(GPIOB, GPIO::Pin::p4),  GPIO(GPIOB, GPIO::Pin::p5),
      } {}

bool DistanceService::is_reading(Position sensor) {
    if ((config::enabledDistanceSensors & configMask[sensor]) == 0) {
        return false;
    }

    return !this->sensors[sensor].is_active();
}

} // namespace raiju
