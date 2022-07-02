#include "Ticker.hpp"

namespace raiju {

Ticker::Ticker(uint32_t target) : target(target) {
    ticks = hal::mcu::get_tick();
}

void Ticker::reset() {
    ticks = hal::mcu::get_tick();
}

uint32_t Ticker::get() const {
    return hal::mcu::get_tick() - ticks;
}

bool Ticker::expired() const {
    return get() > target;
}

} // namespace raiju
