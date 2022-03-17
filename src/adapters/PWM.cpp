#include "PWM.hpp"

namespace raiju {

PWM::PWM(hal::TIM timer, hal::TIM::Channel channel, bool start) : _timer(timer), _ch(channel) {
    if (start) {
        _timer.start_pwm(_ch);
        _timer.set_compare(_ch, 0);
    }
}

void PWM::set(uint32_t value) {
    _timer.set_compare(_ch, value);
}

void PWM::set_frequency(uint32_t freq_hz) {
    uint16_t preescaler_value = (720000 / freq_hz) - 1; // TODO: Get the 72MHz from somewhere
    _timer.set_prescaler(preescaler_value);
}

void PWM::start_dma(uint32_t* data, size_t size) {
    _timer.start_pwm_with_dma(_ch, data, size);
}

} // namespace raiju
