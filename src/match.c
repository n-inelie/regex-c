#include "match.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

inline void match_pretty_print(const Match *m) {
    if (m->set) {
        printf(ANSI_COLOR_CYAN "[MATCH] " ANSI_COLOR_RESET
                               "from:" ANSI_COLOR_GREEN " %zu" ANSI_COLOR_RESET
                               ", to:" ANSI_COLOR_GREEN
                               " %zu\n" ANSI_COLOR_RESET,
               m->from, m->to);
    } else {
        printf(ANSI_COLOR_CYAN "[MATCH]" ANSI_COLOR_RESET ANSI_COLOR_RED
                               " not set\n" ANSI_COLOR_RESET);
    }
}

MatchList *create_match_list(const size_t capacity) {
    MatchList *ml = malloc(sizeof(*ml));
    if (ml == NULL) {
        fprintf(stderr, "malloc error: failed to create MatchList\n");
        return NULL;
    }
    ml->items = malloc(sizeof(Match) * capacity);
    if (ml->items == NULL) {
        fprintf(stderr, "malloc error: failed to create MatchList\n");
        return NULL;
    }
    ml->capacity = capacity;
    ml->length = 0;
    return ml;
}

inline void match_list_destroy(MatchList *ml) {
    free(ml->items);
    free(ml);
}

void match_list_pretty_print(const MatchList *ml) {
    for (size_t i = 0; i < ml->length; ++i) {
        match_pretty_print(ml->items + i);
    }
}

void match_list_append(MatchList *ml, Match m) {
    if (ml->length == ml->capacity) {
        ml->capacity *= 3 / 2;
        ml->items = realloc(ml->items, sizeof(Match) * ml->capacity);
        if (!ml->items) {
            fprintf(stderr,
                    "realloc error: could not append Match to MatchList\n");
            return;
        }
    }
    ml->items[ml->length++] = m;
}

void match_list_pretty_print_text(MatchList *ml, const char *text) {
    size_t current_i = 0;
    for (size_t ml_i = 0; ml_i < ml->length; ++ml_i) {
        Match *match = &ml->items[ml_i];
        if (!match->set) {
            continue;
        }
        printf("%.*s" ANSI_BG_MAGENTA "%.*s" ANSI_COLOR_RESET,
               (int)(match->from - current_i), text + current_i,
               (int)(match->to - match->from + 1), text + match->from);
        current_i = match->to + 1;
    }
    printf("%s\n", text + current_i);
}
