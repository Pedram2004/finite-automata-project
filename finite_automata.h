#ifndef PROJECT_1_DFA_FINITE_AUTOMATA_H
#define PROJECT_1_DFA_FINITE_AUTOMATA_H

#include <map>
#include <vector>

class FiniteAutomata {
protected:
    int initial_state;
    int alphabet_num;
    std::vector<int> final_states;
    std::map<int, std::vector<int>> transition_graph;

    int transition_function(int current_state, int alphabet_letter) {
        return this->transition_graph[current_state][alphabet_letter];
    }
};

#endif
