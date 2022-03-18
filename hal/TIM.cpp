#include <cstdint>

#include "main.h"

#include "inc/TIM.hpp"

namespace hal {

TIM::TIM(TIM_HandleTypeDef* htim) : htim(htim) {}

void TIM::start_it() {
    HAL_TIM_Base_Start_IT(this->htim);
    set_counter(0);
}

void TIM::start_pwm(Channel channel) {
    HAL_TIM_PWM_Start(this->htim, channel);
}

void TIM::start_pwm_with_dma(Channel channel, uint32_t* data, size_t size) {
    HAL_TIM_PWM_Start_DMA(this->htim, channel, data, size);
}

uint32_t TIM::get_counter() const {
    return __HAL_TIM_GET_COUNTER(this->htim);
}

void TIM::set_counter(uint32_t cnt) {
    __HAL_TIM_SET_COUNTER(this->htim, cnt);
}

void TIM::set_prescaler(uint32_t value) {
    __HAL_TIM_SET_PRESCALER(this->htim, value);
}

void TIM::set_compare(Channel channel, uint32_t value) {
    __HAL_TIM_SET_COMPARE(this->htim, channel, value);
}

TIM_TypeDef* TIM::instance() const {
    return this->htim->Instance;
}

} // namespace hal
