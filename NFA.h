#ifndef DFA_NFA_H
#define DFA_NFA_H

#include "dfa.h"

class NFA : protected FiniteAutomata<std::set<int>> {
private:
    std::set<int> create_initial_state();

    bool is_dfa_state_final(const std::set<int> &_dfa_state);

    std::map<std::set<int>, std::vector<std::set<int>>> create_transition_graph(const std::set<int> &_initial_state);

    std::pair<std::set<int>, std::map<int, std::vector<int>>>
    transition_graph_updated(const std::set<int> &_old_initial_state,
                             const std::map<std::set<int>, std::vector<std::set<int>>> &nfa_transition_graph);

    static int
    add_to_rename_table(const std::set<int> &_state, int &_new_state_name, std::set<std::set<int>> &_added_states,
                        std::map<std::set<int>, int> &_rename_table);

public:
    DFA convert_to_dfa();

};


#endif
