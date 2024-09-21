#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct state {
    struct state *transitions[128];
    size_t index;
} State;

typedef struct {
    State **state_list;
    size_t state_count;
    size_t current_state_index;
} Engine;

Engine *engine_create(void);
void engine_destroy(Engine *engine);

void engine_add_transition(Engine *engine, const size_t state_index_from,
                           const size_t state_index_to,
                           const unsigned char symbol);

void state_list_pretty_print(State **state_list, size_t state_count);

bool engine_match_text(Engine *engine, const char *text);
Engine *engine_from_ir(char *ir_string);
