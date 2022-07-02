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
    friend class SmallStepsStrategy;
    friend class StarStrategy;
    friend class StartLeftStrategy;

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
    declState(StrategyState, Ticker leaveTicker; bool leaving; bool ran_initial;);
    declState(RCCheckState, );
    declState(RCState, Ticker leaveTicker; bool leaving;);
    declState(SensorCheckState, );

public:
    FSM();

    void init();
    void cycle();

    void set_state(State& state);

    // void set_start_strategy(Strategy& strategy);
    // void set_round_strategy(Strategy& strategy);

    void run_start_strategy();
    void run_round_strategy();

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

    State* state;

    Strategy* start_strategy = nullptr;
    Strategy* round_strategy = nullptr;

    uint8_t start_strategy_idx;
    uint8_t round_strategy_idx;

    void process_bt();
    void report_config();
};

} // namespace raiju

#endif // __FSM_HPP__
