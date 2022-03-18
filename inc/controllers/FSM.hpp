#if !defined(__FSM_HPP__)
#define __FSM_HPP__

#include "hal.hpp"

#include "WS2812.hpp"

#include "BuzzerService.hpp"
#include "DisplayService.hpp"
#include "DistanceService.hpp"
#include "DrivingService.hpp"
#include "LEDService.hpp"
#include "RadioService.hpp"

#define declState(StateName)                                                                                           \
    class StateName : public State {                                                                                   \
    public:                                                                                                            \
        void enter(FSM* fsm);                                                                                          \
        void cycle(FSM* fsm);                                                                                          \
        void exit(FSM* fsm);                                                                                           \
        static State& instance();                                                                                      \
        ~StateName();                                                                                                  \
                                                                                                                       \
    private:                                                                                                           \
        StateName() {}                                                                                                 \
    }

namespace raiju {

class FSM {
public:
    class State {
    public:
        virtual void enter(FSM* fsm) = 0;
        virtual void cycle(FSM* fsm) = 0;
        virtual void exit(FSM* fsm) = 0;
        virtual ~State() {}
    };

    declState(IdleState);

public:
    FSM();

    void init();
    void cycle();

    void set_state(State& state);

private:
    // DistanceService s_distance;
    // DisplayService s_display;
    RadioService s_radio;
    DrivingService s_driving;
    LEDService s_led;
    BuzzerService s_buzzer;

    hal::GPIO button;

    State* state;
};

} // namespace raiju

#endif // __FSM_HPP__
