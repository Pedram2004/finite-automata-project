#include "finite_automata.h"

template<typename T>
FiniteAutomata<T>::FiniteAutomata(int _init_state, int _alphabet_number, std::set<int> &_final_states,
                                  std::map<int, std::vector<T>> &_transition_graph) {
    this->initial_state = _init_state;
    this->alphabet_number = _alphabet_number;
    this->final_states = std::set<int>(_final_states);
    this->transition_graph = std::map<int, std::vector<T>>(_transition_graph);

}

template<typename T>
bool FiniteAutomata<T>::is_state_final(int _state) {
    return this->final_states.count(_state);
}

template<typename T>
T FiniteAutomata<T>::transition_function(int _current_state, int _alphabet_letter) {
    return this->transition_graph[_current_state][_alphabet_letter];
}

// FiniteAutomata::string class Definition

template<typename T>
std::string FiniteAutomata<T>::string::get_internal_string() {
        return this->internal_string;
}

template<typename T>
int FiniteAutomata<T>::string::length() {
        return this->internal_string.length();
}

template<typename T>
bool FiniteAutomata<T>::string::operator<(const FiniteAutomata::string &other_string) const {
        return this->internal_string.length() < other_string.internal_string.length();
}

template<typename T>
typename FiniteAutomata<T>::string FiniteAutomata<T>::string::operator+(const char &character) const {
        return string(this->internal_string + character);
}