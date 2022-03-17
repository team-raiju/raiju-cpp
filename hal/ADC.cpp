#include "inc/ADC.hpp"

namespace hal {

ADC::ADC(ADC_HandleTypeDef* hadc) : hadc(hadc) {}

void ADC::start_dma(uint32_t* buffer, size_t size) {
    HAL_ADC_Start_DMA(hadc, buffer, size);
}

void ADC::stop_dma() {
    HAL_ADC_Stop_DMA(hadc);
}

} // namespace hal
