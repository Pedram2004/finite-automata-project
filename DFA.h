#ifndef DFA_DFA_H
#define DFA_DFA_H

#include "finite_automata.h"
#include <string>

class DFA : protected FiniteAutomata {
    using FiniteAutomata::FiniteAutomata;

private:
    std::vector<std::pair<std::string, int>> depth_limited_first_search(int max_depth);

public:

    DFA(int initial_state, int alphabet_num, std::vector<int> &final_states,
        std::map<int, std::vector<int>> &transition_graph) :
            FiniteAutomata(initial_state, alphabet_num, final_states, transition_graph) {}

    bool is_string_accepted(std::string const &_string);

    std::vector<std::string> specific_length_strings(int _string_length);

    std::vector<std::string> strings_accepted();
};

#endif
