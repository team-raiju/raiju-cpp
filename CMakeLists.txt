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

set(STM_DRIVERS_FOLDER /usr/share/STM32CubeF1/Drivers)

set(STM32CUBE_GENERATED_FILES
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c

    cube/Src/main.c
    cube/Src/stm32f1xx_hal_msp.c
    cube/Src/stm32f1xx_it.c
    cube/Src/system_stm32f1xx.c

    cube/startup_stm32f103xg.s
)

set(HAL_FILES
    hal/UART.cpp
    hal/GPIO.cpp
    hal/TIM.cpp
    hal/ADC.cpp
    hal/mcu.cpp
)

set(EXECUTABLE ${PROJECT_NAME}.out)
add_executable(${EXECUTABLE}
    ${STM32CUBE_GENERATED_FILES}
    ${HAL_FILES}
    src/main.cpp
    src/config.cpp
    src/debug.cpp

    src/adapters/ADCDMA.cpp
    src/adapters/PPM.cpp
    src/adapters/PWM.cpp
    src/adapters/WS2812.cpp
    src/adapters/Ticker.cpp

    src/controllers/FSM.cpp
    src/controllers/AutoWaitState.cpp
    src/controllers/IdleState.cpp
    src/controllers/InitState.cpp
    src/controllers/StrategyState.cpp
    src/controllers/RCState.cpp
    src/controllers/SensorCheckState.cpp
    src/controllers/RCCheckState.cpp

    src/services/BuzzerService.cpp
    src/services/BluetoothService.cpp
    src/services/DisplayService.cpp
    src/services/DistanceService.cpp
    src/services/DrivingService.cpp
    src/services/LEDService.cpp
    src/services/LineService.cpp
    src/services/RadioService.cpp
    src/services/UartRadioService.cpp
    src/services/StartModuleService.cpp

    src/strategies/StarStrategy.cpp
    src/strategies/SmallStepsStrategy.cpp
    src/strategies/StartLeftStrategy.cpp
)

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DUSE_HAL_DRIVER
    # -DUART_DEBUG
    # -DUART_RADIO
    -DSTM32F103xG

    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    cube/Inc
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Inc
    ${STM_DRIVERS_FOLDER}/STM32F1xx_HAL_Driver/Inc/Legacy
    ${STM_DRIVERS_FOLDER}/CMSIS/Device/ST/STM32F1xx/Include
    ${STM_DRIVERS_FOLDER}/CMSIS/Include
)

target_include_directories(${EXECUTABLE} PRIVATE
    hal
    inc
    inc/adapters
    inc/controllers
    inc/services
    inc/strategies
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
