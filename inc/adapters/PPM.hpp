#if !defined(__PPM_HPP__)
#define __PPM_HPP__

#include "hal.hpp"

namespace raiju {

class PPM : public hal::mcu::exti_interruptible, public hal::mcu::tim_interruptible {
private:
    hal::GPIO _ppm_in;
    hal::TIM _timer;

    uint16_t _value;
    uint16_t _tmp_count;
    uint32_t _fail_count;

public:
    static const uint16_t min_value_ms = 1000;
    static const uint16_t stopped_value_ms = 1500;
    static const uint16_t max_value_ms = 2000;

    static const uint16_t failsafe_max_timer_overflow = 10;

    PPM(hal::GPIO gpio, hal::TIM timer);

    uint16_t value() const;
    uint16_t constrained_value() const;

    void on_interrupt(uint16_t GPIO_Pin);
    void on_interrupt(TIM_HandleTypeDef* htim);
};

} // namespace raiju

#endif // __PPM_HPP__
