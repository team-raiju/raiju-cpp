#if !defined(__DISTANCE_SERVICE_HPP__)
#define __DISTANCE_SERVICE_HPP__

#include <cstdint>

#include "hal.hpp"

namespace raiju {

class DistanceService {
public:
    // Position in the sensors array, depends on physical connection
    enum Position : uint8_t {
        RIGHT = 4,
        BRIGHT = 5,
        FRONT = 6,
        BLEFT = 7,
        LEFT = 8,
    };

    // Maps a Position (array index) to a mask for config::enabledDistanceSensors
    static const uint8_t configMask[];

    DistanceService();

    bool is_reading(Position sensor);

private:
    hal::GPIO sensors[9];
};

} // namespace raiju

#endif // __DISTANCE_SERVICE_HPP__
