#include <algorithm>

#include "utils.h"

#include "DrivingService.hpp"

#define COUNTER_PERIOD_MAX (1000)
#define MAX_SPEED 100

using hal::TIM, hal::GPIO;

namespace raiju {

DrivingService::DrivingService()
    : right_motor{
          PWM(TIM(&htim1), TIM::Channel::ch2),
          PWM(TIM(&htim1), TIM::Channel::ch1),
      },
      left_motor{
          PWM(TIM(&htim1), TIM::Channel::ch4),
          PWM(TIM(&htim1), TIM::Channel::ch3),
      },
      _en(GPIOA, GPIO::Pin::p13) {}

void DrivingService::drive(int16_t left, int16_t right) {
    enable();

    left = constrain(left, -99, 99);
    right = constrain(right, -99, 99);

    if (std::abs(left) < 10) {
        left = 0;
    }

    if (std::abs(right) < 10) {
        right = 0;
    }

    left = map<int16_t, int16_t>(left, -MAX_SPEED, MAX_SPEED, -COUNTER_PERIOD_MAX, COUNTER_PERIOD_MAX);
    right = map<int16_t, int16_t>(right, -MAX_SPEED, MAX_SPEED, -COUNTER_PERIOD_MAX, COUNTER_PERIOD_MAX);

    set_motor(left_motor, left);
    set_motor(right_motor, right);
}

void DrivingService::stop() {
    drive(0, 0);
    disable();
}

void DrivingService::enable() {
    _en.reset();
}

void DrivingService::disable() {
    _en.set();
}

void DrivingService::set_motor(PWM motor[2], int32_t speed) {
    if (speed < 0) {
        motor[0].set(-speed);
        motor[1].set(0);
    } else {
        motor[0].set(0);
        motor[1].set(speed);
    }
}

} // namespace raiju
