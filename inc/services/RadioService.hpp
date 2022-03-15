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

private:
    PPM ppms[4];
};

} // namespace raiju

#endif // __RADIO_SERVICE_HPP__
