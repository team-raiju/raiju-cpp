#if !defined(__LIB_MCU_HPP__)
#define __LIB_MCU_HPP__

namespace hal::mcu {

class exti_interruptible {
public:
    virtual void on_interrupt(uint16_t GPIO_Pin) = 0;
};

class tim_interruptible {
public:
    virtual void on_interrupt(TIM_HandleTypeDef* htim) = 0;
};

class adc_interruptible {
public:
    virtual void on_interrupt(ADC_HandleTypeDef* htim) = 0;
};

typedef void (*exti_cb_fn)();

void init();
void sleep(const uint32_t ms);

void add_exti_interrupt(exti_interruptible* interruptible);
void add_tim_interrupt(tim_interruptible* interruptible);
void add_adc_interrupt(adc_interruptible* interruptible);

} // namespace hal::mcu

#endif // __LIB_MCU_HPP__
