#include "../utils.h"
#include "engine.h"

#include <stdio.h>

void state_list_pretty_print(State **state_list, size_t state_count) {
    for (size_t i = 0; i < state_count; ++i) {
        State *state = state_list[i];
        printf(ANSI_COLOR_MAGENTA "q%zu:\n" ANSI_COLOR_RESET, i);
        for (size_t j = 0; j < 128; ++j) {
            State *next_state = state->transitions[j];
            if (next_state != NULL) {
                printf("  \'" ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET
                       "\' -> " ANSI_COLOR_MAGENTA "q%zu\n" ANSI_COLOR_RESET,
                       (char)j, next_state->index);
            }
        }
    }
}
