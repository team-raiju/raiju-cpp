#if !defined(__BUZZER_SERVICE_HPP__)
#define __BUZZER_SERVICE_HPP__

#include "PWM.hpp"

namespace raiju {

class BuzzerService {
public:
    BuzzerService();

    void play_tetris();
    void play_megalovania();

private:
    PWM buzzer;
};

} // namespace raiju

#endif // __BUZZER_SERVICE_HPP__
