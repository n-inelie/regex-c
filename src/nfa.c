#include "nfa.h"

#include <stdio.h>
#include <stdlib.h>

NFA *nfa_create(void) {
    NFA *nfa = malloc(sizeof(*nfa));
    if (nfa == NULL) {
        fprintf(stderr, "malloc error: failed to create nfa");
    }
    nfa->start_state = state_create();
    nfa->end_state = state_create();
    return nfa;
}

inline void nfa_destroy(NFA *nfa) {
    state_destroy(nfa->start_state);
    state_destroy(nfa->end_state);
}

inline NFA *nfa_from_epsilon(void) {
    NFA *nfa = nfa_create();
    state_append_epsilon_transition(nfa->start_state, nfa->end_state);
    return nfa;
}

inline NFA *nfa_from_symbol(const symbol c) {
    NFA *nfa = nfa_create();
    state_append_transition(nfa->start_state, nfa->end_state, c);
    return nfa;
}

NFA *nfa_concat(const size_t n, NFA **nfas) {
    if (n < 2) {
        fprintf(stderr, "nfa_concat error: minimum 2 nfas required\n");
        return NULL;
    }
    for (size_t i = 0; i < n - 1; ++i) {
        NFA *nfa1 = nfas[i];
        NFA *nfa2 = nfas[i + 1];
        state_copy(nfa1->end_state, nfa2->start_state);
    }
    NFA *result = nfa_create();
    result->start_state = nfas[0]->start_state;
    result->end_state = nfas[n - 1]->end_state;
    return result;
}

NFA *nfa_union(const size_t n, NFA **nfas) {
    if (n < 2) {
        fprintf(stderr, "nfa_union error: minimum 2 nfas required\n");
        return NULL;
    }
    NFA *result = nfa_create();
    for (size_t i = 0; i < n; ++i) {
        state_append_epsilon_transition(result->start_state, nfas[i]->start_state);
        state_append_epsilon_transition(nfas[i]->end_state, result->end_state);
    }
    return result;
}

NFA *nfa_closure(NFA *nfa) {
    NFA *result = nfa_from_epsilon();
    state_append_epsilon_transition(result->start_state, nfa->start_state);
    state_append_epsilon_transition(nfa->end_state, nfa->start_state);
    state_append_epsilon_transition(nfa->end_state, result->start_state);
    return result;
}
