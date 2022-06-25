#include "LineService.hpp"
#include "config.hpp"

namespace raiju {

// This must match src/app/ui/tabs/config-tab/config-tab.page.ts in the app
const uint8_t LineService::configMask[] = {
    0,      // Battery
    1 << 2, // BL
    1 << 0, // FL1
    1 << 1, // FR1
    0,      // FR2
    1 << 3, // BR
    0,      // FL2
};

LineService::LineService() {
    adcs = &ADCDMA::instance();
}

bool LineService::is_white(Position pos) {
    if ((config::enabledLineSensors & configMask[pos]) == 0) {
        return false;
    }

    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos) < white_threshold;
}

uint16_t LineService::raw_reading(Position pos) {
    if ((config::enabledLineSensors & configMask[pos]) == 0) {
        return false;
    }

    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos);
}

void LineService::start() {
    adcs->start();
}

} // namespace raiju
