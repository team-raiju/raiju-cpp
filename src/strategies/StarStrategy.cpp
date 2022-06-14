#include "Strategy.hpp"
#include "StrategyParams.hpp"

namespace raiju {

StarStrategy::StarStrategy() : Strategy() {}

void StarStrategy::run(FSM* fsm, StrategyParams const& params) {}

Strategy& StarStrategy::instance() {
    static StarStrategy strategy;
    return strategy;
}

StarStrategy::~StarStrategy() {}

} // namespace raiju
