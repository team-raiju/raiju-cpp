// We don't have RTT so we'll use the display's UART for debug if enabled
// This should be temporary

#include <string>

#include "config.hpp"
#include "hal.hpp"

#if defined(UART_DEBUG)
namespace raiju::debug {

static hal::UART uart(&huart1);

void log(std::string data) {
    uart.transmit((uint8_t*)data.data(), data.size());
}

} // namespace raiju::debug

#endif // UART_DEBUG