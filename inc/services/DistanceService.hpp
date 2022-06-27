#if !defined(__DISTANCE_SERVICE_HPP__)
#define __DISTANCE_SERVICE_HPP__

#include <cstdint>
#include <map>

#include "hal.hpp"

namespace raiju {

class DistanceService {
public:
    // Position in the sensors array, depends on physical connection
    enum Position : uint8_t {
        L = 7,
        FL = 8,
        DL = 0, // TODO
        F = 6,
        DR = 0, // TODO
        FR = 4,
        R = 5,
    };

    // Maps a Position (array index) to a mask for config::enabledDistanceSensors
    static const std::map<Position, uint8_t> configMask;

    DistanceService();

    bool is_reading(Position sensor);

private:
    hal::GPIO sensors[9];
};

} // namespace raiju

#endif // __DISTANCE_SERVICE_HPP__
