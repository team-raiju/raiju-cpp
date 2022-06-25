#if !defined(__TICKER_HPP__)
#define __TICKER_HPP__

#include "hal.hpp"

namespace raiju {

class Ticker {
public:
    Ticker(uint32_t target = 0xFFFFFFFF);

    void reset();
    uint32_t get();
    bool expired();

private:
    uint32_t ticks;
    uint32_t target;
};

} // namespace raiju

#endif // __TICKER_HPP__
