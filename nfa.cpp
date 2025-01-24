#include "nfa.h"
#include <deque>

std::set<int> NFA::create_initial_state() {
    std::set<int> epsilon_reached_states = this->transition_function(this->initial_state, this->alphabet_number);
    epsilon_reached_states.insert(this->initial_state);
    return epsilon_reached_states;
}

bool NFA::is_dfa_state_final(const std::set<int> &_dfa_state) {
    for (const int &separate_state: _dfa_state) {
        if (this->is_state_final(separate_state)) {
            return true;
        }
    }

    return false;
}

std::map<std::set<int>, std::vector<std::set<int>>> NFA::create_transition_graph(const std::set<int> &_initial_state) {
    std::map<std::set<int>, std::vector<std::set<int>>> new_transition_graph;

    std::deque<std::set<int>> creation_queue{_initial_state};
    std::set<std::set<int>> visited_states;

    while (!creation_queue.empty()) {
        std::set<int> current_state = creation_queue.front();
        creation_queue.pop_front();
        visited_states.insert(current_state);

        new_transition_graph[current_state] = std::vector<std::set<int>>(this->alphabet_number);

        for (int letter = 0; letter < this->alphabet_number; letter++) {
            std::set<int> reaching_states;

            for (const int &separate_state: current_state) {

                for (int reaching_state: this->transition_function(separate_state, letter)) {
                    reaching_states.insert(reaching_state);

                    for (int epsilon_reached_state: this->transition_function(reaching_state, this->alphabet_number)) {
                        reaching_states.insert(epsilon_reached_state);
                    }
                }
            }

            new_transition_graph[current_state][letter] = reaching_states;

            if (!visited_states.count(reaching_states)) {
                creation_queue.push_back(reaching_states);
            }
        }
    }

    return new_transition_graph;
}

int NFA::add_to_rename_table(const std::set<int> &_state, int &_new_state_name, std::set<std::set<int>> &_added_states,
                             std::map<std::set<int>, int> &_rename_table) {

    if (!_added_states.count(_state)) {
        _added_states.insert(_state);
        _rename_table[_state] = _new_state_name;
        _new_state_name++;
    }

    return _rename_table[_state];
}

std::pair<std::set<int>, std::map<int, std::vector<int>>>
NFA::transition_graph_updated(const std::set<int> &_old_initial_state,
                              const std::map<std::set<int>, std::vector<std::set<int>>> &nfa_transition_graph) {

    std::map<int, std::vector<int>> new_transition_graph;
    std::set<int> final_states;

    std::map<std::set<int>, int> rename_table;
    std::set<std::set<int>> added_states;

    int new_name_state = 0;

    rename_table[_old_initial_state] = new_name_state;

    for (const auto &old_state: nfa_transition_graph) {
        int new_assigned_name = NFA::add_to_rename_table(old_state.first, new_name_state, added_states, rename_table);
        new_transition_graph[new_assigned_name] = std::vector<int>(this->alphabet_number);

        if (this->is_dfa_state_final(old_state.first)) {
            final_states.insert(rename_table[old_state.first]);
        }

        int index = 0;
        for (const auto &reaching_state: old_state.second) {
            new_transition_graph[new_assigned_name][index] = NFA::add_to_rename_table(
                    reaching_state, new_name_state, added_states, rename_table);
            index++;

            if (this->is_dfa_state_final(reaching_state)) {
                final_states.insert(rename_table[reaching_state]);
            }
        }
    }

    return std::make_pair(final_states, new_transition_graph);


}

DFA NFA::convert_to_dfa() {
    std::set<int> new_initial_state = this->create_initial_state();

    auto dfa_transition_graph = this->create_transition_graph(new_initial_state);

    auto pair_data= this->transition_graph_updated(new_initial_state, dfa_transition_graph);

    std::set<int> dfa_final_states = pair_data.first;
    std::map<int, std::vector<int>> renamed_dfa_transition_graph = pair_data.second;

    return {DFA(0, this->alphabet_number, dfa_final_states, renamed_dfa_transition_graph)};

}