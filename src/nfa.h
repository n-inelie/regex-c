#pragma once

#include "state.h"

typedef struct {
    State *start_state;
    State *end_state;
} NFA;

NFA *nfa_create(void);
void nfa_destroy(NFA *nfa);

NFA *nfa_from_epsilon(void);
NFA *nfa_from_symbol(const symbol c);

NFA *nfa_concat(const size_t n, NFA **nfas);
NFA *nfa_union(const size_t n, NFA **nfas);
NFA *nfa_closure(NFA *nfa);
