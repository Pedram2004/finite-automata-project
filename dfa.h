#ifndef DFA_DFA_H
#define DFA_DFA_H

// #include <iostream>
#include "finite_automata.h"

class DFA : protected FiniteAutomata<int> {
private:
    static const int INFINITY;

    std::vector<FiniteAutomata::string>
    strings_length_between(unsigned int lower_bound, unsigned int upper_bound, int max_result_num = -1);

    const std::set<std::set<int>> * procedure_mark();

    std::set<std::pair<std::set<int>, bool>> partitioning(std::set<std::set<int>> const * _unmarked_pairs);

    static int find_state(int state_wanted, const std::map<int, std::set<int>> &_new_old_states);

    std::map<int, std::vector<int>> creating_new_transition_graph(const std::map<int, std::set<int>> &_new_old_states);

public:

    DFA(int _init_state, int _alphabet_number, std::set<int> &_final_states,
        std::map<int, std::vector<int>> &_transition_graph) : FiniteAutomata<int>(_init_state, _alphabet_number,
                                                                                  _final_states,
                                                                                  _transition_graph) {};

    bool is_string_accepted(std::string &_string);

    std::vector<std::string> specific_length_strings(int _length);

    std::vector<std::string> strings_accepted();

    std::string longest_string();

    std::string shortest_string();

    DFA minimize_dfa();

    friend std::ostream& operator<<(std::ostream& os, const DFA& dfa);

};


#endif
