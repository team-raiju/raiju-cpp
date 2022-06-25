#if !defined(__STRATEGY_HPP__)
#define __STRATEGY_HPP__

#include "Ticker.hpp"

#define declStrategy(StrategyName, extras)                                                                             \
    class StrategyName : public Strategy {                                                                             \
    public:                                                                                                            \
        void run(FSM* fsm);                                                                                            \
        static Strategy& instance();                                                                                   \
        ~StrategyName();                                                                                               \
                                                                                                                       \
    private:                                                                                                           \
        StrategyName();                                                                                                \
        extras                                                                                                         \
    }

namespace raiju {

class FSM;

class Strategy {
protected:
    Strategy() {}

public:
    virtual void run(FSM* fsm) = 0;

    virtual ~Strategy(){};
};

declStrategy(SmallStepsStrategy, bool still; Ticker stepTicker;);
declStrategy(StarStrategy, );

}

#endif // __STRATEGY_HPP__
