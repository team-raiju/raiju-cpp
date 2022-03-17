#include <cstring>

#include "utils.h"

#include "hal.hpp"

#include "ADCDMA.hpp"

namespace raiju {

ADCDMA::ADCDMA() : adc(hal::ADC(&hadc1)) {}

ADCDMA& ADCDMA::instance() {
    static ADCDMA s;
    return s;
}

void ADCDMA::start() {
    reading_done = false;
    adc.start_dma(dma_buffer, amount * readings_per_adc);
}

void ADCDMA::calculate_readings_and_restart() {
    if (!reading_done) {
        return;
    }

    memset(aux_readings, 0, amount * sizeof(uint32_t));

    for (size_t i = 0; i < (amount * readings_per_adc); i += amount) {
        for (size_t j = 0; j < amount; j++) {
            aux_readings[j] += dma_buffer[i + j];
        }
    }

    for (size_t j = 0; j < amount; j++) {
        readings[j] = aux_readings[j] / ((amount * readings_per_adc) / amount);
    }

    start();
}

uint32_t ADCDMA::get_reading(size_t idx) const {
    idx = min(idx, amount - 1);
    return readings[idx];
}

} // namespace raiju
