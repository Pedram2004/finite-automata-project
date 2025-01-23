#include "dfa.h"
#include <deque>
#include <limits>
#include <algorithm>
#include <iostream>

const int DFA::INFINITY = std::numeric_limits<int>::max();

bool DFA::is_string_accepted(std::string &_string) {
    int current_state = this->initial_state;
    for (char letter: _string) {
        current_state = this->transition_function(current_state, letter - '0');
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
                auto child_vertex = std::make_pair(
                        current_string + (char) ('0' + i),
                        this->transition_function(current_state, i));

                if (current_state != child_vertex.second) {
                    search_queue.push_back(child_vertex);
                }
            }
        }

        if (lower_bound <= current_string.length() && current_string.length() <= upper_bound) {
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
    return FiniteAutomata::string::to_string_conversion(this->strings_length_between(_length, _length, -1));
}

std::vector<std::string> DFA::strings_accepted() {
    return FiniteAutomata::string::to_string_conversion(this->strings_length_between(0, DFA::INFINITY, 20));
}

std::string DFA::longest_string() {
    std::vector<FiniteAutomata::string> _strings_accepted = this->strings_length_between(0, DFA::INFINITY, -1);
    auto p_longest_string = std::max_element(_strings_accepted.begin(), _strings_accepted.end());
    return p_longest_string->get_internal_string();
}

std::string DFA::shortest_string() {
    return (this->strings_length_between(0, DFA::INFINITY, 1).begin())->get_internal_string();
}

// dfa minimization functions

const std::set<std::set<int>> *DFA::procedure_mark() {
    auto unmarked_pairs = new std::set<std::set<int>>();
    for (const auto &key_value_1: this->transition_graph) {
        int state1 = key_value_1.first;

        for (const auto &key_value_2: this->transition_graph) {
            int state2 = key_value_2.first;

            if (state1 != state2) {

                bool is_state1_final = this->is_state_final(key_value_1.first);
                bool is_state2_final = this->is_state_final(key_value_2.first);

                std::set<int> pair{state1, state2};

                if ((is_state1_final && is_state2_final) ^ (!is_state1_final && !is_state2_final)) {
                    unmarked_pairs->insert(pair);
                }
            }
        }
    }

    bool no_marked_pairs = false;

    while (!no_marked_pairs) {
        no_marked_pairs = true;
        auto set_iter = unmarked_pairs->begin();
        while (set_iter != unmarked_pairs->end()) {
            bool is_marked = false;
            for (int i = 0; i < this->alphabet_number; i++) {
                const std::set<int> &pair = *set_iter;
                std::set<int> transitioned_pair{
                        this->transition_function(*(pair.begin()), i),
                        this->transition_function(*(++pair.begin()), i)
                };

                if (!unmarked_pairs->count(transitioned_pair) &&
                    (*transitioned_pair.begin() != *(++transitioned_pair.begin()))) {
                    set_iter = unmarked_pairs->erase(set_iter);
                    no_marked_pairs = false;
                    is_marked = true;
                    break;
                }
            }

            if (is_marked) {
                set_iter++;
            }
        }
    }

    return unmarked_pairs;
}

std::set<std::pair<std::set<int>, bool>> DFA::partitioning(const std::set<std::set<int>> *_unmarked_pairs) {

    auto other_element = [](int _element, const std::set<int> &_pair) {
        if (*(_pair.begin()) == _element) {
            return *(--_pair.end());
        } else {
            return *(_pair.begin());
        }
    };

    std::set<std::pair<std::set<int>, bool>> states_partition;

    std::set<int> visited_states;

    for (const auto &pair_iter: this->transition_graph) {
        int current_state = pair_iter.first;

        if (!visited_states.count(current_state)) {
            std::set<int> new_state;
            bool is_new_state_final = this->is_state_final(current_state);

            for (const auto &pair: *_unmarked_pairs) {
                if (pair.count(current_state)) {
                    int indistinguishable_element = other_element(current_state, pair);
                    new_state.insert(indistinguishable_element);
                    visited_states.insert(indistinguishable_element);

                    if (!is_new_state_final) {
                        is_new_state_final = this->is_state_final(indistinguishable_element);
                    }
                }
            }

            states_partition.insert(std::make_pair(new_state, is_new_state_final));
        }
    }

    return states_partition;
}

int DFA::find_state(int state_wanted, const std::map<int, std::set<int>> &_new_old_states) {
    for (const auto &_new_old_state: _new_old_states) {
        if (_new_old_state.second.count(state_wanted)) {
            return _new_old_state.first;
        }
    }
    return -1;
}

std::map<int, std::vector<int>>
DFA::creating_new_transition_graph(const std::map<int, std::set<int>> &_new_old_states) {
    std::map<int, std::vector<int>> new_transition_graph;


    for (const auto &new_old_state: _new_old_states) {
        std::vector<int> resulting_states;
        for (int i = 0; i < this->alphabet_number; i++) {
            int old_resulting_state = this->transition_function(*(new_old_state.second.begin()), i);
            int new_resulting_state = DFA::find_state(old_resulting_state, _new_old_states);
            resulting_states.push_back(new_resulting_state);
        }
        new_transition_graph.insert(std::pair<int, std::vector<int>>(new_old_state.first, resulting_states));
    }

    return new_transition_graph;
}

DFA DFA::minimize_dfa() {
    const std::set<std::set<int>> *indistinguishable_pairs = this->procedure_mark();
    std::set<std::pair<std::set<int>, bool>> partitions = this->partitioning(indistinguishable_pairs);

    std::map<int, std::set<int>> new_old_states;
    std::set<int> new_final_states;


    int new_state_number = 0;
    for (const auto &state_type_pair: partitions) {
        new_old_states.insert(std::make_pair(new_state_number, state_type_pair.first));
        if (state_type_pair.second) {
            new_final_states.insert(new_state_number);
        }
        new_state_number++;
    }

    auto new_transition_graph = this->creating_new_transition_graph(new_old_states);

    return {DFA(DFA::find_state(this->initial_state, new_old_states), this->alphabet_number, new_final_states,
                new_transition_graph)};
}