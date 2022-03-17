#if !defined(__RADIO_SERVICE_HPP__)
#define __RADIO_SERVICE_HPP__

#include <cstdint>

#include "PPM.hpp"
#include "hal.hpp"

namespace raiju {

class RadioService {
public:
    struct Coordinate {
        int8_t x, y;
    };

public:
    RadioService();

    Coordinate coordinates() const;

    int16_t get_ch1() const;
    int16_t get_ch2() const;
    int16_t get_ch3() const;
    int16_t get_ch4() const;

private:
    PPM ppms[4];
};

} // namespace raiju

#endif // __RADIO_SERVICE_HPP__
