#include "FSM.hpp"

namespace raiju {

FSM::FSM() : button(GPIOC, hal::GPIO::Pin::p15) {
    state = &InitState::instance();
}

void FSM::init() {
    this->state->enter(this);
}

void FSM::cycle() {
    this->state->cycle(this);
}

void FSM::set_state(State& state) {
    this->state->exit(this);
    this->state = &state;
    this->state->enter(this);
}

} // namespace raiju
