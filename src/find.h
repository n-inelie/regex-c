#include "nfa.h"
#include "match.h"

State *state_find_next(State *state, symbol c);
Match match_find(NFA *nfa, const char *text);
