#include "FSM.hpp"

namespace raiju {

FSM::FSM() : led(GPIOB, hal::GPIO::Pin::p1), button(GPIOC, hal::GPIO::Pin::p15) {
    state = &IdleState::instance();
}

void FSM::init() {}

void FSM::cycle() {
    state->cycle(this);
}

void FSM::set_state(State &state) {
    this->state->exit(this);
    this->state = &state;
    this->state->enter(this);
}

} // namespace raiju
