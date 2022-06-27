#include "LineService.hpp"
#include "config.hpp"

namespace raiju {

// This must match src/app/ui/tabs/config-tab/config-tab.page.ts in the app
const std::map<LineService::Position, uint8_t> LineService::configMask = {
    { LineService::Position::Battery, 0 },  { LineService::Position::BL, 1 << 2 },
    { LineService::Position::FL1, 1 << 0 }, { LineService::Position::FR1, 1 << 1 },
    { LineService::Position::FR2, 0 },      { LineService::Position::BR, 1 << 3 },
    { LineService::Position::FL2, 0 },
};

LineService::LineService() {
    adcs = &ADCDMA::instance();
}

bool LineService::is_white(Position pos) {
    if ((config::enabledLineSensors & configMask.at(pos)) == 0) {
        return false;
    }

    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos) < white_threshold;
}

uint16_t LineService::raw_reading(Position pos) {
    if ((config::enabledLineSensors & configMask.at(pos)) == 0) {
        return false;
    }

    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos);
}

void LineService::start() {
    adcs->start();
}

} // namespace raiju
