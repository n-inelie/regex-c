#pragma once

#include <stddef.h>

typedef struct state {
    struct state *transitions[128];
    struct state **epsilon_transitions;
    size_t epsilon_transitions_n;
} State;

State *state_create(void);
void state_destroy(State *state);
void state_copy(State *dest, State *src);

typedef char symbol;

void state_append_transition(State *state, State *next_state, const symbol c);
void state_append_epsilon_transition(State *state, State *next_state);

void state_pretty_print(const State *state);
