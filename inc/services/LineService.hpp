#if !defined(__LINE_SERVICE_HPP__)
#define __LINE_SERVICE_HPP__

#include "ADCDMA.hpp"

namespace raiju {

class LineService {
public:
    static const int white_threshold = 500;

    enum Position {
        Battery = 0, // Gambi
        FR1 = 1,
        FR2 = 2,
        FL1 = 3,
        FL2 = 4,
        BR = 5,
        BL = 6,
    };

    LineService();

    bool is_white(Position pos);
    uint16_t raw_reading(Position pos);

    void start();

private:
    ADCDMA* adcs;
};

} // namespace raiju

#endif // __LINE_SERVICE_HPP__
