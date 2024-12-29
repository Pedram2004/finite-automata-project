#include "DFA.h"
#include <deque>


std::vector<std::pair<std::string, int>> DFA::depth_limited_first_search(int specific_depth) {
    std::vector<std::pair<std::string, int>> strings_states;
    std::deque<std::tuple<std::string, int, int>> stack;

    stack.emplace_front("", this->initial_state, 0);

    while (!stack.empty()) {
        auto current_vertex = stack.front();

        int current_vertex_depth = std::get<2>(current_vertex);
        int current_state = std::get<1>(current_vertex);
        std::string generated_string = std::get<0>(current_vertex);

        if (current_vertex_depth < specific_depth) {
            for (int i = 0; i <= this->alphabet_number; i++) {
                int child_state = this->transition_function(current_state, i);
                if (child_state != current_state) {
                    stack.emplace_front(generated_string + (char) i, child_state, current_vertex_depth + 1);
                }
            }
        } else if (current_vertex_depth == specific_depth) {
            strings_states.emplace_back(generated_string, current_state);
        }
    }

    return strings_states;
}

bool DFA::is_string_accepted(std::string const &_string) {
    int current_state = this->initial_state;
    for (auto letter: _string) {
        int int_letter = letter - '0';
        current_state = DFA::transition_function(current_state, int_letter);
    }
    return this->is_state_final(current_state);
}

std::vector<std::string> DFA::specific_length_strings(int _string_length) {
    std::vector<std::string> specific_length_strings;

    auto strings_states = this->depth_limited_first_search(_string_length);

    for (const auto &string_state_pair: strings_states) {
        if (this->is_state_final(string_state_pair.second)) {
            specific_length_strings.push_back(string_state_pair.first);
        }
    }

    return specific_length_strings;
}

