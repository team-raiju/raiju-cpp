#if !defined(__LIB_GPIO_HPP__)
#define __LIB_GPIO_HPP__

#include "main.h"

namespace hal {

class GPIO {
public:
    enum Pin {
        p0 = GPIO_PIN_0,
        p1 = GPIO_PIN_1,
        p2 = GPIO_PIN_2,
        p3 = GPIO_PIN_3,
        p4 = GPIO_PIN_4,
        p5 = GPIO_PIN_5,
        p6 = GPIO_PIN_6,
        p7 = GPIO_PIN_7,
        p8 = GPIO_PIN_8,
        p9 = GPIO_PIN_9,
        p10 = GPIO_PIN_10,
        p11 = GPIO_PIN_11,
        p12 = GPIO_PIN_12,
        p13 = GPIO_PIN_13,
        p14 = GPIO_PIN_14,
        p15 = GPIO_PIN_15,
    };

    GPIO(GPIO_TypeDef *port, Pin pin);
    Pin pin() const;

    void toggle();
    void set();
    void reset();

    bool is_active();

private:
    GPIO_TypeDef *_port;
    Pin _pin;
};

} // namespace hal

#endif // __LIB_GPIO_HPP__
