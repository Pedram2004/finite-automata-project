#ifndef DFA_FINITE_AUTOMATA_H
#define DFA_FINITE_AUTOMATA_H

#include <vector>
#include <set>
#include <map>

template<typename T>
class FiniteAutomata {
    /* NFA and DFA parent class
     * must include a transition function for both of them (including epsilon moves of NFA) */
protected:
    int initial_state{}, alphabet_number{};
    std::set<int> final_states;
    std::map<int, std::vector<T>> transition_graph;

    FiniteAutomata(int _init_state, int _alphabet_number, std::set<int> &_final_states,
                   std::map<int, std::vector<T>> &_transition_graph) {
        this->initial_state = _init_state;
        this->alphabet_number = _alphabet_number;
        this->final_states = std::set<int>(_final_states);
        this->transition_graph = std::map<int, std::vector<T>> (_transition_graph);

    }

    bool is_state_final(int _state) {
        return this->final_states.count(_state);
    }

    T transition_function(int _current_state, int _alphabet_letter) {
        return this->transition_graph[_current_state][_alphabet_letter];
    }
};

#endif
