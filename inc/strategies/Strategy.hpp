#if !defined(__STRATEGY_HPP__)
#define __STRATEGY_HPP__

#include "StrategyParams.hpp"

#define declStrategy(StrategyName, extras)                                                                             \
    class StrategyName : public Strategy {                                                                             \
    public:                                                                                                            \
        void run(FSM* fsm, StrategyParams const& params);                                                              \
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
    virtual void run(FSM* fsm, StrategyParams const& params) = 0;

    virtual ~Strategy() {};
};

declStrategy(SmallStepsStrategy, );
declStrategy(StarStrategy, );

}

#endif // __STRATEGY_HPP__
