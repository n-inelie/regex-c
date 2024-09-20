#include "find.h"

#include <string.h>

void test_find(void) {
    NFA *nfa =
        nfa_union(2, (NFA *[]){
                         nfa_concat(3,
                                    (NFA *[]){
                                        nfa_from_symbol('a'),
                                        nfa_from_symbol('b'),
                                        nfa_from_symbol('c'),
                                    }),
                         nfa_concat(2,
                                    (NFA *[]){
                                        nfa_closure(nfa_from_symbol('p')),
                                        nfa_from_symbol('q'),
                                    }),
                     });
    char buffer[(1 << 22)];
    memset(buffer, 'x', sizeof(buffer));
    buffer[sizeof(buffer) - 10] = 'a';
    buffer[sizeof(buffer) - 9] = 'b';
    buffer[sizeof(buffer) - 8] = 'c';
    Match m = match_find(nfa, buffer);
    match_pretty_print(&m);
}

void test_match(void) {
    MatchList *ml = create_match_list(8);
    match_list_append(ml, (Match){3, 7, true});
    match_list_append(ml, (Match){10, 12, true});
    match_list_pretty_print(ml);
    match_list_pretty_print_text(ml, "sora is a beautiful font");
    match_list_destroy(ml);
}

void test_state(void) {
    State *first = state_create();
    State *second = state_create();
    State *third = state_create();

    state_append_transition(first, second, 'a');
    state_append_transition(first, second, 'b');
    state_append_transition(first, third, 'd');
    state_append_epsilon_transition(first, third);

    state_append_transition(second, third, 'x');
    state_append_transition(second, third, 'y');
    state_append_epsilon_transition(second, first);

    state_pretty_print(first);
    state_pretty_print(second);
    state_pretty_print(third);

    state_destroy(first);
    state_destroy(second);
    state_destroy(third);
}
