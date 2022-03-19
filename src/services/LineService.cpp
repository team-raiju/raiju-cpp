#include "LineService.hpp"

namespace raiju {

LineService::LineService() {
    adcs = &ADCDMA::instance();
}

bool LineService::is_white(Position pos) {
    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos) < white_threshold;
}

uint16_t LineService::raw_reading(Position pos) {
    adcs->calculate_readings_and_restart();
    return adcs->get_reading(pos);
}

void LineService::start() {
    adcs->start();
}

} // namespace raiju
