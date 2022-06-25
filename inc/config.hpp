#include <cstdint>

#if !defined(__CONFIG_HPP__)
#define __CONFIG_HPP__

namespace raiju::config {

extern uint8_t enabledDistanceSensors;
extern uint8_t enabledLineSensors;
extern uint8_t reverseSpeed;
extern uint8_t reverseTimeMs;
extern uint8_t turnSpeed;
extern uint8_t turnTimeMs;
extern uint8_t stepWaitTimeMs;
extern uint8_t maxMotorSpeed;

} // namespace raiju

#endif // __CONFIG_HPP__
