#include "engine.h"

#include <stdbool.h>

bool engine_match_text(Engine *engine, const char *text) {
    State *potential_next_state;
    size_t i = 0;
    unsigned char c = text[i];

    while (c != '\0') {
        potential_next_state =
            engine->state_list[engine->current_state_index]->transitions[c];
        if (potential_next_state) {
            engine->current_state_index = potential_next_state->index;
        } else {
            engine->current_state_index = 0;
        }
        c = text[++i];
    }
    if (engine->current_state_index == engine->state_count - 1) {
        return true;
    }
    return false;
}
