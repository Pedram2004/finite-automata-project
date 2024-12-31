#include "dfa.h"
#include <deque>
#include <limits>
#include <algorithm>

const int DFA::INFINITY = std::numeric_limits<int>::max();

bool DFA::is_string_accepted(std::string &_string) {
    int current_state = this->initial_state;
    for (char letter: _string) {
        current_state = this->transition_function(current_state, letter);
    }
    return this->is_state_final(current_state);
}

std::vector<FiniteAutomata<int>::string>
DFA::strings_length_between(unsigned int lower_bound, unsigned int upper_bound, int max_result_num) {
    std::vector<FiniteAutomata::string> cumulated_strings;
    auto search_queue = std::deque<std::pair<FiniteAutomata::string, int>>{
            std::make_pair(FiniteAutomata::string(""), this->initial_state)};

    while (!search_queue.empty()) {
        std::pair<FiniteAutomata::string, int> current_vertex = search_queue.front();
        search_queue.pop_front();

        FiniteAutomata::string current_string = current_vertex.first;
        int current_state = current_vertex.second;

        if (current_string.length() < upper_bound) {
            for (int i = 0; i < this->alphabet_number; i++) {
                auto child_vertex = std::make_pair(current_string + (char) ('0' + i),
                                                   this->transition_function(current_state, i));

                if (current_state != child_vertex.second) {
                    search_queue.push_back(current_vertex);
                }
            }

        } else if (lower_bound <= current_string.length() <= upper_bound) {
            if (this->is_state_final(current_state)) {
                cumulated_strings.push_back(current_string);

                if (cumulated_strings.size() == max_result_num && max_result_num != -1) {
                    return cumulated_strings;
                }
            }
        }

    }
    return cumulated_strings;
}

std::vector<std::string> DFA::specific_length_strings(int _length) {
    return this->strings_length_between(_length, _length, -1);
}

std::vector<std::string> DFA::strings_accepted() {
    return this->strings_length_between(0, DFA::INFINITY, 20);
}

std::string DFA::longest_string() {
    auto _strings_accepted = this->strings_length_between(0, DFA::INFINITY, -1);
    auto v = std::max_element(_strings_accepted.begin(), strings_accepted().end());
}

std::string DFA::shortest_string() {
    return (this->strings_length_between(0, DFA::INFINITY, 1).begin())->get_internal_string();
}

