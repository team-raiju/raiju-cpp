#include "utils.h"

#include "DrivingService.hpp"

#define COUNTER_PERIOD_MAX (100)

using hal::TIM, hal::GPIO;

namespace raiju {

DrivingService::DrivingService()
    : left_motor{
          PWM(TIM(&htim1), TIM::Channel::ch1),
          PWM(TIM(&htim1), TIM::Channel::ch2),
      },
      right_motor{
          PWM(TIM(&htim1), TIM::Channel::ch3),
          PWM(TIM(&htim1), TIM::Channel::ch4),
      },
      _en(GPIOA, GPIO::Pin::p13) {}

void DrivingService::drive(int16_t left, int16_t right) {
    left = constrain(left, -99, 99);
    right = constrain(right, -99, 99);

    if (abs(left) < 10) {
        left = 0;
    }

    if (abs(right) < 10) {
        right = 0;
    }

    left = map<int16_t, int16_t>(left, -100, 100, -COUNTER_PERIOD_MAX, COUNTER_PERIOD_MAX);
    right = map<int16_t, int16_t>(right, -100, 100, -COUNTER_PERIOD_MAX, COUNTER_PERIOD_MAX);

    set_motor(left_motor, left);
    set_motor(right_motor, right);
}

void DrivingService::enable() {
    _en.set();
}

void DrivingService::disable() {
    _en.reset();
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
