#if !defined(__LIB_TIM_HPP__)
#define __LIB_TIM_HPP__

#include "main.h"

namespace hal {

class TIM {
public:
    TIM();

private:
    TIM_HandleTypeDef *htim;
    uint32_t channel;
};

} // namespace hal

#endif // __LIB_TIM_HPP__
