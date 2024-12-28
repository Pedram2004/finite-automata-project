#include "DFA.h"
#include <deque>
#include <algorithm>

std::vector<std::string> DFA::depth_limited_first_search(int specific_depth) {
    std::vector<std::string> strings_states;
    std::deque<std::tuple<std::string, int, int>> stack;

    stack.emplace_front("", this->initial_state, 0);

    while (!stack.empty()) {
        auto current_vertex = stack.front();

        int current_vertex_depth = std::get<2>(current_vertex);
        int current_state = std::get<1>(current_vertex);
        std::string created_string = std::get<0>(current_vertex);

        if (current_vertex_depth < specific_depth) {
            for (int i = 0; i <= this->alphabet_number; i++) {
                int child_state = this->transition_function(current_state, i);
                if (child_state != current_state) {
                    stack.emplace_front(created_string + (char) i, child_state, current_vertex_depth + 1);
                }
            }
        } else if (current_vertex_depth == specific_depth) {
            strings_states.push_back(created_string);
        }
    }

    return strings_states;
}

bool DFA::is_string_accepted(std::string const &_string) {
    unsigned int current_state = this->initial_state;
    for (auto letter: _string) {
        int int_letter = letter - '0';
        current_state = DFA::transition_function((int) current_state, int_letter);
    }
    auto final_states = &this->final_states;
    return std::find((*final_states).begin(), (*final_states).end(), current_state) != (*final_states).end();
}


std::vector<std::string> DFA::specific_length_strings(int _string_length) {
    std::vector<std::string> specific_length_strings;

    auto strings_states = this->depth_limited_first_search(_string_length);

    for (const auto &_string: strings_states) {
        if (this->is_string_accepted(_string)) {
            specific_length_strings.push_back(_string);
        }
    }

    return specific_length_strings;
}
