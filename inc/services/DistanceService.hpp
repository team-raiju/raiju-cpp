#if !defined(__DISTANCE_SERVICE_HPP__)
#define __DISTANCE_SERVICE_HPP__

#include <cstdint>

#include "hal.hpp"

namespace raiju {

class DistanceService {
private:
    hal::GPIO sensors[9];

public:
    DistanceService();

    bool is_reading(uint8_t sensor);
};

} // namespace raiju

#endif // __DISTANCE_SERVICE_HPP__
