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
std::vector<std::string>
FiniteAutomata<T>::string::to_string_conversion(std::vector<FiniteAutomata<T>::string> const &FA_string_vector) {
    std::vector<std::string> string_list;
    string_list.reserve(FA_string_vector.size());
    for (FiniteAutomata::string FA_string: FA_string_vector) {
        string_list.push_back(FA_string.get_internal_string());
    }
    return string_list;
}

template<typename T>
std::string FiniteAutomata<T>::string::get_internal_string() {
    return std::string(this->internal_string);
}

template<typename T>
int FiniteAutomata<T>::string::length() {
    return this->internal_string.length();
}

template<typename T>
bool FiniteAutomata<T>::string::operator<(const FiniteAutomata<T>::string &other_string) const {
    return this->internal_string.length() < other_string.internal_string.length();
}

template<typename T>
typename FiniteAutomata<T>::string FiniteAutomata<T>::string::operator+(const char &character) const {
    return string(this->internal_string + character);
}

// for compile process

template
class FiniteAutomata<int>;

template
class FiniteAutomata<std::set<int>>;