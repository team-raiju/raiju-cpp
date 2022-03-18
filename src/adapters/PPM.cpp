#include "utils.h"

#include "PPM.hpp"

namespace raiju {

PPM::PPM(hal::GPIO gpio, hal::TIM timer) : _ppm_in(gpio), _timer(timer) {
    hal::mcu::add_exti_interrupt(this);
    hal::mcu::add_tim_interrupt(this);

    _value = PPM::stopped_value_ms;
    timer.start_it();
}

uint16_t PPM::value() const {
    return _value;
}

uint16_t PPM::constrained_value() const {
    return constrain(_value, PPM::min_value_ms, PPM::max_value_ms);
}

void PPM::on_interrupt(uint16_t GPIO_Pin) {
    if (GPIO_Pin == this->_ppm_in.pin()) {
        if (_ppm_in.is_active()) {
            _tmp_count = _timer.get_counter();
        } else {
            _value = _timer.get_counter() - _tmp_count;
            _fail_count = 0;
        }
    }
}

void PPM::on_interrupt(TIM_HandleTypeDef* htim) {
    if (htim->Instance == _timer.instance()) {
        _fail_count++;

        if (_fail_count > PPM::failsafe_max_timer_overflow) {
            _value = PPM::stopped_value_ms;
        }
    }
}

} // namespace raiju
