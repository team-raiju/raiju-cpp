#include "StartModuleService.hpp"

namespace raiju {

StartModuleService::StartModuleService() : enable(GPIOB, hal::GPIO::Pin::p15), reading(GPIOA, hal::GPIO::Pin::p2) {
    enable.set();
}

bool StartModuleService::is_start() {
    return reading.is_active();
}

void StartModuleService::reset() {
    enable.reset();
    hal::mcu::sleep(1000);
    enable.set();
}

} // namespace raiju'
