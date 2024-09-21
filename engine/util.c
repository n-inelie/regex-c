#include "engine.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline Engine *engine_create(void) {
    Engine *engine = malloc(sizeof(*engine));
    assert(engine != NULL);
    engine->state_list = NULL;
    engine->state_count = 0;
    engine->current_state_index = 0;
    return engine;
}

inline void engine_destroy(Engine *engine) {
    for (size_t i = 0; i < engine->state_count; ++i) {
        free(engine->state_list[i]);
    }
    free(engine->state_list);
    free(engine);
}

inline void engine_add_transition(Engine *engine, const size_t state_index_from,
                                  const size_t state_index_to,
                                  const unsigned char symbol) {
    assert(engine->state_count > state_index_from &&
           engine->state_count > state_index_to);
    engine->state_list[state_index_from]->transitions[symbol] =
        engine->state_list[state_index_to];
}
