#include "config.hpp"

namespace raiju::config {

uint8_t enabledDistanceSensors = 0b01101011; // R, FR, DR, F, DL, FL, L
uint8_t enabledLineSensors = 0xFF;
uint8_t reverseSpeed = 100;
uint8_t reverseTimeMs = 120;
uint8_t turnSpeed = 100;
uint8_t turnTimeMs = 70;
uint8_t stepWaitTimeMs = 100;
uint8_t maxMotorSpeed = 100;

} // namespace raiju::config
