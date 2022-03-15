#if !defined(__PWM_HPP__)
#define __PWM_HPP__

#include "hal.hpp"

namespace raiju {

class PWM {
public:
    PWM(hal::TIM timer, hal::TIM::Channel channel);

    void set(uint32_t value);

private:
    hal::TIM _timer;
    hal::TIM::Channel _ch;
};

} // namespace raiju

#endif // __PWM_HPP__
