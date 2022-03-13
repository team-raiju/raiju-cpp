#if !defined(__LIB_MCU_HPP__)
#define __LIB_MCU_HPP__

namespace hal::mcu {

class exti_interruptible {
public:
    virtual void on_interrupt(uint16_t GPIO_Pin) = 0;
};

typedef void (*exti_cb_fn)();

void init();
void sleep(const uint32_t ms);

void add_exti_interrupt(exti_interruptible *interruptible);

} // namespace hal::mcu

#endif // __LIB_MCU_HPP__
