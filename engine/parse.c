#include "engine.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void engine_allocate_state_list(Engine *engine) {
    engine->state_list = malloc(sizeof(State *) * engine->state_count);
    assert(engine->state_list != NULL);

    for (size_t i = 0; i < engine->state_count; ++i) {
        State *state = malloc(sizeof(State));
        assert(state != NULL);
        state->index = i;
        memset(state->transitions, 0, sizeof(state->transitions));
        engine->state_list[i] = state;
    }
}

Engine *engine_from_ir(char *ir_string) {
    Engine *engine = engine_create();
    size_t state_index_from, state_index_to;
    unsigned char symbol;

    char *ir_line = strtok(ir_string, "\n");
    sscanf(ir_line, "qcount %zu", &(engine->state_count));
    ir_string = NULL;
    ir_line = strtok(ir_string, "\n");

    engine_allocate_state_list(engine);

    while (ir_line != NULL) {
        sscanf(ir_line, "q%zu q%zu %c", &state_index_from, &state_index_to,
               &symbol);
        engine_add_transition(engine, state_index_from, state_index_to, symbol);

        ir_string = NULL;
        ir_line = strtok(ir_string, "\n");
    }

    return engine;
}
