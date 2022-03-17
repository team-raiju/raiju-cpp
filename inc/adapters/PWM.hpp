#if !defined(__PWM_HPP__)
#define __PWM_HPP__

#include "hal.hpp"

namespace raiju {

class PWM {
public:
    PWM(hal::TIM timer, hal::TIM::Channel channel, bool start = true);

    void set(uint32_t value);
    void set_frequency(uint32_t value);
    void start_dma(uint32_t* data, size_t size);

private:
    hal::TIM _timer;
    hal::TIM::Channel _ch;
};

} // namespace raiju

#endif // __PWM_HPP__
