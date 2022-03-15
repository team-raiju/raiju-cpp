#include "PWM.hpp"

namespace raiju {

PWM::PWM(hal::TIM timer, hal::TIM::Channel channel) : _timer(timer), _ch(channel) {
    _timer.start_pwm(_ch);
    _timer.set_compare(_ch, 0);
}

void PWM::set(uint32_t value) {
    _timer.set_compare(_ch, value);
}

} // namespace raiju
