#if !defined(__DISTANCE_SERVICE_HPP__)
#define __DISTANCE_SERVICE_HPP__

#include <cstdint>

#include "hal.hpp"

namespace raiju {

class DistanceService {
public:
    DistanceService();

    bool is_reading(uint8_t sensor);

private:
    hal::GPIO sensors[9];
};

} // namespace raiju

#endif // __DISTANCE_SERVICE_HPP__
