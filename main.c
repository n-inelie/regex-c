#include "utils.h"
#include "engine/engine.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    char ir_string[1 << 12];
    FILE *ir_file = fopen("examples/ir_example_0.txt", "rb");
    assert(ir_file != NULL);
    fread(ir_string, sizeof(char), 1 << 12, ir_file);
    fclose(ir_file);

    Engine *engine = engine_from_ir(ir_string);
    state_list_pretty_print(engine->state_list, engine->state_count);

    const char *const samples[] = {
        "abc", "bc", "abbbbc", "ac", "bbbbc", "ab",
    };

    for (size_t i = 0; i < ARRAY_SIZE(samples); ++i) {
        const char *text = samples[i];
        printf("(" ANSI_COLOR_YELLOW "%zu" ANSI_COLOR_RESET ") ", i);
        if (engine_match_text(engine, text)) {
            printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, text);
            continue;
        }
        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET, text);
    }

    engine_destroy(engine);

    return 0;
}
