#if !defined(__STRATEGY_HPP__)
#define __STRATEGY_HPP__

#include <string>

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
    std::string name;
    virtual void run(FSM* fsm) = 0;

    virtual ~Strategy(){};
};

declStrategy(SmallStepsStrategy, bool still; bool attacking; Ticker attackTicker; Ticker stepTicker;);
declStrategy(StarStrategy, bool attacking; Ticker attackTicker;);
declStrategy(StartLeftStrategy, );
declStrategy(StartRightStrategy, );


}

#endif // __STRATEGY_HPP__
