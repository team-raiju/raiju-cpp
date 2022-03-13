#include "FSM.hpp"

namespace raiju {

FSM::FSM() {
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
