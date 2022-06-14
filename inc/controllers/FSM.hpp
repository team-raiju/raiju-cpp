#if !defined(__FSM_HPP__)
#define __FSM_HPP__

#include "hal.hpp"

#include "WS2812.hpp"

#include "Strategy.hpp"

#include "BluetoothService.hpp"
#include "BuzzerService.hpp"
#include "DisplayService.hpp"
#include "DistanceService.hpp"
#include "DrivingService.hpp"
#include "LEDService.hpp"
#include "LineService.hpp"
#include "RadioService.hpp"
#include "StartModuleService.hpp"

#define declState(StateName, extras)                                                                                   \
    class StateName : public State {                                                                                   \
    public:                                                                                                            \
        void enter(FSM* fsm);                                                                                          \
        void cycle(FSM* fsm);                                                                                          \
        void exit(FSM* fsm);                                                                                           \
        static State& instance();                                                                                      \
        ~StateName();                                                                                                  \
                                                                                                                       \
    private:                                                                                                           \
        StateName();                                                                                                   \
        extras                                                                                                         \
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

    declState(InitState, );
    declState(IdleState, bool start_led;);
    declState(AutoWaitState, );
    declState(StrategyState, uint32_t ticker; uint32_t ticker_fail; bool still; bool leaving;);
    declState(RCCheckState, );
    declState(RCState, uint32_t ticker; bool leaving;);
    declState(SensorCheckState, );

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

    Strategy* start_strategy_idx = nullptr;
    StrategyParams start_strategy_params;

    Strategy* round_strategy_idx = nullptr;
    StrategyParams round_strategy_params;
};

} // namespace raiju

#endif // __FSM_HPP__
