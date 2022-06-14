#include "Strategy.hpp"
#include "StrategyParams.hpp"

namespace raiju {

SmallStepsStrategy::SmallStepsStrategy() : Strategy() {}

void SmallStepsStrategy::run(FSM* fsm, StrategyParams const& params) {}

Strategy& SmallStepsStrategy::instance() {
    static SmallStepsStrategy strategy;
    return strategy;
}

SmallStepsStrategy::~SmallStepsStrategy() {}

} // namespace raiju
