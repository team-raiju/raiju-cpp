#if !defined(__LINE_SERVICE_HPP__)
#define __LINE_SERVICE_HPP__

#include <cstdint>
#include <map>

#include "ADCDMA.hpp"

namespace raiju {

class LineService {
public:
    static const int white_threshold = 2500;

    // Position in the ADC array, depends on physical connection
    enum Position : uint8_t {
        Battery = 0, // Gambi
        FR1 = 3,     // ou 4,
        BR = 5,      // ou 6,
        FL1 = 2,
        BL = 1,
        FR2 = 4,
        FL2 = 6,
    };

    // Maps a Position (array index) to a mask for config::enabledLineSensors
    static const std::map<Position, uint8_t> configMask;

    LineService();

    bool is_white(Position pos);
    uint16_t raw_reading(Position pos);

    void start();

private:
    ADCDMA* adcs;
};

} // namespace raiju

#endif // __LINE_SERVICE_HPP__
