#if !defined(__FSM_HPP__)
#define __FSM_HPP__

#include "hal.hpp"

#include "WS2812.hpp"

#include "BluetoothService.hpp"
#include "BuzzerService.hpp"
#include "DisplayService.hpp"
#include "DistanceService.hpp"
#include "DrivingService.hpp"
#include "LEDService.hpp"
#include "LineService.hpp"
#include "RadioService.hpp"
#include "StartModuleService.hpp"

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

    declState(InitState);
    declState(IdleState);
    declState(AutoWaitState);
    declState(StrategyState);
    declState(RCCheckState);
    declState(RCState);
    declState(SensorCheckState);

public:
    FSM();

    void init();
    void cycle();

    void set_state(State& state);

private:
    DistanceService s_distance;
    // DisplayService s_display;
    BluetoothService s_bt;
    RadioService s_radio;
    DrivingService s_driving;
    LEDService s_led;
    StartModuleService s_smodule;
    BuzzerService s_buzzer;
    LineService s_line;

    hal::GPIO button;

    State* state;
};

} // namespace raiju

#endif // __FSM_HPP__
