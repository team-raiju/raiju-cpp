#include "config.hpp"
#include "hal.hpp"

#include "DistanceService.hpp"

using hal::GPIO;

namespace raiju {

// clang-format off
// This must match src/app/ui/tabs/config-tab/config-tab.page.ts in the app
const std::map<DistanceService::Position, uint8_t> DistanceService::configMask = {
    { DistanceService::Position::L,  1 << 0 },
    { DistanceService::Position::FL, 1 << 1 },
    { DistanceService::Position::DL, 1 << 2 },
    { DistanceService::Position::F,  1 << 3 },
    { DistanceService::Position::DR, 1 << 4 },
    { DistanceService::Position::FR, 1 << 5 },
    { DistanceService::Position::R,  1 << 6 },
};

DistanceService::DistanceService()
    : sensors{
          GPIO(GPIOB, GPIO::Pin::p0),
          GPIO(GPIOC, GPIO::Pin::p13),
          GPIO(GPIOC, GPIO::Pin::p14),
          GPIO(GPIOC, GPIO::Pin::p10),
          GPIO(GPIOC, GPIO::Pin::p11),
          GPIO(GPIOC, GPIO::Pin::p12),
          GPIO(GPIOD, GPIO::Pin::p2),
          GPIO(GPIOB, GPIO::Pin::p4),
          GPIO(GPIOB, GPIO::Pin::p5),
      } {}
// clang-format on

bool DistanceService::is_reading(Position sensor) {
    if ((config::enabledDistanceSensors & configMask.at(sensor)) == 0) {
        return false;
    }

    return !this->sensors[sensor].is_active();
}

} // namespace raiju
