#include "find.h"

State *state_find_next(State *state, symbol c) {
    State *maybe = state->transitions[(int)c];
    if (maybe != NULL) {
        return maybe;
    }
    for (size_t i = 0; i < state->epsilon_transitions_n; ++i) {
        maybe = state_find_next(state->epsilon_transitions[i], c);
        if (maybe != NULL) {
            return maybe;
        }
    }
    if (state->epsilon_transitions_n == 1) {
        return state->epsilon_transitions[0];
    }
    return NULL;
}

Match match_find(NFA *nfa, const char *text) {
    Match m = {0, 0, false};
    State *state = nfa->start_state;
    size_t i = 0;
    while (text[i] != '\0') {
        state = state_find_next(state, text[i]);
        if (state == NULL) {
            state = nfa->start_state;
            ++i;
            m.set = false;
            continue;
        }
        if (!m.set) {
            m.from = i;
            m.set = true;
        }
        if (state == nfa->end_state) {
            m.to = i;
            return m;
        }
        ++i;
    }
    m.set = false;
    return m;
}
