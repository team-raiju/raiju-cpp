cmake_minimum_required(VERSION 3.15.3)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(raiju)

enable_language(CXX C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(STM32CUBE_GENERATED_FILES
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c

    cube/Src/main.c
    cube/Src/stm32f1xx_hal_msp.c
    cube/Src/stm32f1xx_it.c
    cube/Src/system_stm32f1xx.c

    cube/startup_stm32f103xg.s
)

set(HAL_FILES
    hal/GPIO.cpp
    hal/TIM.cpp
    hal/mcu.cpp
)

set(EXECUTABLE ${PROJECT_NAME}.out)
add_executable(${EXECUTABLE}
    ${STM32CUBE_GENERATED_FILES}
    ${HAL_FILES}
    src/main.cpp
    src/controllers/FSM.cpp
    src/controllers/IdleState.cpp
    src/services/DistanceService.cpp
)

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DUSE_HAL_DRIVER
    -DSTM32F103xG

    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    cube/Inc
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc
    /usr/share/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    /usr/share/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    /usr/share/STM32CubeF1/Drivers/CMSIS/Include
)

target_include_directories(${EXECUTABLE} PRIVATE
    hal
    inc/controllers
    inc/services
)

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m3
    -mthumb

    -fdata-sections
    -ffunction-sections
    -fno-exceptions

    -Wall

    $<$<CONFIG:Debug>:-Og>
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${CMAKE_SOURCE_DIR}/cube/STM32F103RFTx_FLASH.ld
    -mcpu=cortex-m3
    -mthumb
    -specs=nano.specs
    -specs=nosys.specs
    -lc
    -lm
    -lnosys
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
)

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${EXECUTABLE}
)

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
)
