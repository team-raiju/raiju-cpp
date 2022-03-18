#if !defined(__MULTI_ADC_HPP__)
#define __MULTI_ADC_HPP__

#include "hal.hpp"

namespace raiju {

class ADCDMA : hal::mcu::adc_interruptible {
public:
    static const size_t amount = 7;
    static const size_t readings_per_adc = 256;

    // This class must be instantiated only once, as we only have a single DMA for every ADC in this handler
    // Services can get this instance to retrieve values for different channels
    static ADCDMA& instance();

    void start();
    void calculate_readings_and_restart();
    uint32_t get_reading(size_t idx) const;

    void on_interrupt(ADC_HandleTypeDef* hadc);

private:
    ADCDMA();

    hal::ADC adc;

    uint32_t dma_buffer[amount * readings_per_adc];
    uint32_t readings[amount];
    uint32_t aux_readings[amount];

    bool reading_done;
};

} // namespace raiju

#endif // __MULTI_ADC_HPP__
