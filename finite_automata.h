#ifndef DFA_FINITE_AUTOMATA_H
#define DFA_FINITE_AUTOMATA_H

#include <vector>
#include <set>
#include <map>
#include <string>

template<typename T>
class FiniteAutomata {

protected:

    class string {
    private:
        std::string internal_string;
    public:
        explicit string(std::string _string) : internal_string(std::move(_string)) {};

        std::string get_internal_string() {
            return this->internal_string;
        }

        int length() {
            return this->internal_string.length();
        }

        bool operator<(string const &other_string) const {
            return this->internal_string.length() < other_string.internal_string.length();
        };

        string operator+(char const &character) const {
            return string(this->internal_string + character);
        }
    };

    int initial_state{}, alphabet_number{};
    std::set<int> final_states;
    std::map<int, std::vector<T>> transition_graph;

    FiniteAutomata(int _init_state, int _alphabet_number, std::set<int> &_final_states,
                   std::map<int, std::vector<T>> &_transition_graph);

    bool is_state_final(int _state);

    T transition_function(int _current_state, int _alphabet_letter);
};

#endif
