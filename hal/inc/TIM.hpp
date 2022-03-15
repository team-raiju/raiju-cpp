#if !defined(__LIB_TIM_HPP__)
#define __LIB_TIM_HPP__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim12;

#ifdef __cplusplus
}
#endif

namespace hal {

class TIM {
public:
    enum Channel : uint32_t {
        ch1 = TIM_CHANNEL_1,
        ch2 = TIM_CHANNEL_2,
        ch3 = TIM_CHANNEL_3,
        ch4 = TIM_CHANNEL_4,
    };

    TIM(TIM_HandleTypeDef* htim);

    void start_it();
    void start_pwm(Channel channel);

    uint32_t get_counter() const;
    void set_counter(uint32_t cnt);
    void set_prescaler(uint32_t value);
    void set_compare(Channel channel, uint32_t value);

    TIM_TypeDef* instance() const;

private:
    TIM_HandleTypeDef* htim;
};

} // namespace hal

#endif // __LIB_TIM_HPP__
