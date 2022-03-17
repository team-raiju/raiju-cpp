#if !defined(__ADC_HPP__)
#define __ADC_HPP__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

#ifdef __cplusplus
}
#endif

namespace hal {

class ADC {
public:
    ADC(ADC_HandleTypeDef* hadc);

    void start_dma(uint32_t* buffer, size_t size);
    void stop_dma();

private:
    ADC_HandleTypeDef* hadc;
};

} // namespace hal

#endif // __ADC_HPP__
