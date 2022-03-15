#if !defined(__FSM_HPP__)
#define __FSM_HPP__

#include "DistanceService.hpp"
#include "hal.hpp"

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
    DistanceService s_distance;

    hal::GPIO led;
    hal::GPIO button;

    State* state;
};

} // namespace raiju

#endif // __FSM_HPP__
