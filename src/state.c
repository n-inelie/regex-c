#include "state.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

State *state_create(void) {
    State *state = malloc(sizeof(*state));
    if (state == NULL) {
        fprintf(stderr, "malloc error: failed to create state\n");
        return NULL;
    }
    state->epsilon_transitions = malloc(sizeof(State *));
    if (state->epsilon_transitions == NULL) {
        fprintf(stderr, "malloc error: failed to create state\n");
        return NULL;
    }
    state->epsilon_transitions_n = 0;
    return state;
}

inline void state_destroy(State *state) {
    free(state->epsilon_transitions);
    free(state);
}

void state_copy(State *dest, State *src) {
    memcpy(dest->transitions, src->transitions, sizeof(src->transitions));
    memcpy(dest->epsilon_transitions, src->epsilon_transitions,
           sizeof(State *) * src->epsilon_transitions_n);
    dest->epsilon_transitions_n = src->epsilon_transitions_n;
}

inline void state_append_transition(State *state, State *next_state,
                                    const symbol c) {
    state->transitions[(int)c] = next_state;
}

inline void state_append_epsilon_transition(State *state, State *next_state) {
    state->epsilon_transitions[state->epsilon_transitions_n++] = next_state;
    state->epsilon_transitions =
        realloc(state->epsilon_transitions,
                sizeof(State *) * state->epsilon_transitions_n);
    if (state->epsilon_transitions == NULL) {
        fprintf(
            stderr,
            "realloc error: failed to append epsilon transition to state\n");
    }
}

void state_pretty_print(const State *state) {
    printf("State Transitions: " ANSI_COLOR_GREEN "[ ");
    for (size_t i = 0; i < ARRAY_SIZE(state->transitions); ++i) {
        if (state->transitions[i] != NULL) {
            printf("%c ", (symbol)i);
        }
    }
    printf("]\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE
           "#(" ANSI_COLOR_RESET "State Epsilon Transitions" ANSI_COLOR_BLUE
           ")" ANSI_COLOR_RESET ": " ANSI_COLOR_YELLOW "%zu\n" ANSI_COLOR_RESET,
           state->epsilon_transitions_n);
}
