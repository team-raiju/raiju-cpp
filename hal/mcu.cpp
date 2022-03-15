#include "main.h"

#include "inc/mcu.hpp"

extern "C" {
void SystemClock_Config(void);
}

namespace hal::mcu {

static uint8_t m_exti_amount = 0;
static uint8_t m_tim_amount = 0;

static exti_interruptible* m_exti_ints[10];
static tim_interruptible* m_tim_ints[10];

void init() {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();

    MX_USART1_UART_Init();
    MX_USART3_UART_Init();

    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM7_Init();
    MX_TIM12_Init();

    MX_ADC1_Init();
}

void sleep(const uint32_t ms) {
    HAL_Delay(ms);
}

void add_exti_interrupt(exti_interruptible* interruptible) {
    if (m_exti_amount >= 10) {
        return;
    }

    m_exti_ints[m_exti_amount++] = interruptible;
}

void add_tim_interrupt(tim_interruptible* interruptible) {
    if (m_tim_amount >= 10) {
        return;
    }

    m_tim_ints[m_tim_amount++] = interruptible;
}

} // namespace hal::mcu

/**
 * @brief Interrupt handler for falling and rising edge detection
 *
 * @note This must be outside the namespace to allow linkage with the weak
 * version inside HAL
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    for (uint8_t i = 0; i < hal::mcu::m_exti_amount; i++) {
        hal::mcu::m_exti_ints[i]->on_interrupt(GPIO_Pin);
    }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
    for (uint8_t i = 0; i < hal::mcu::m_exti_amount; i++) {
        hal::mcu::m_exti_ints[i]->on_interrupt(GPIO_Pin);
    }
}

/**
 * @brief Interrupt handler for timer period elapsed
 *
 * @note This must be outside the namespace to allow linkage with the weak
 * version inside HAL
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    for (uint8_t i = 0; i < hal::mcu::m_tim_amount; i++) {
        hal::mcu::m_tim_ints[i]->on_interrupt(htim);
    }
}
