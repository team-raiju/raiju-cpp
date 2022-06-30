#if !defined(__DEBUG_HPP__)
#define __DEBUG_HPP__

#include <string>

#if defined(UART_DEBUG)
#define DEBUG_LOG(x) debug::log(x)

namespace raiju::debug {

void log(std::string data);

} // namespace raiju::debug

#else
#define DEBUG_LOG(x)

#endif // UART_DEBUG
#endif // __DEBUG_HPP__
