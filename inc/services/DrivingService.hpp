#if !defined(__DRIVING_SERVICE_HPP__)
#define __DRIVING_SERVICE_HPP__

#include "hal.hpp"

#include "PWM.hpp"

namespace raiju {

class DrivingService {
public:
    DrivingService();

    void drive(int16_t left, int16_t right);

private:
    PWM left_motor[2];
    PWM right_motor[2];

    hal::GPIO _en;

    void set_motor(PWM motor[2], int32_t speed);
    void enable();
    void disable();
};

} // namespace raiju

#endif // __DRIVING_SERVICE_HPP__
