#if !defined(__BUZZER_SERVICE_HPP__)
#define __BUZZER_SERVICE_HPP__

#include "PWM.hpp"

namespace raiju {

class BuzzerService {
public:
    BuzzerService();

    void play_tetris();
    void play_megalovania();
    void beep(uint16_t duration = 50);

private:
#ifdef STM32F103xG
    PWM buzzer;
#endif
};

} // namespace raiju

#endif // __BUZZER_SERVICE_HPP__
