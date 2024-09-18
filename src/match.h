#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t from;
    size_t to;
    bool set;
} Match;

void match_pretty_print(const Match *m);

typedef struct {
    size_t capacity;
    size_t length;
    Match *items;
} MatchList;

MatchList *create_match_list(const size_t capacity);
void match_list_destroy(MatchList *ml);

void match_list_append(MatchList *ml, Match m);

void match_list_pretty_print(const MatchList *ml);
void match_list_pretty_print_text(MatchList *ml, const char *text);
