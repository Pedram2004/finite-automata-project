#include "nfa.h"
#include <iostream>

int main() {
    std::map<int, std::vector<int>> T1, T2, T3, T4;
    std::set<int> F1 {2, 0}, F2 {2}, F3 {1}, F4 {0, 3}, F5 {2};
    T1[0] = std::vector<int>{1, 1};
    T1[1] = std::vector<int>{2, 3};
    T1[2] = std::vector<int>{3, 3};
    T1[3] = std::vector<int>{3, 3};

    DFA M1 = DFA(0, 2, F1, T1);
    DFA min_M1 = M1.minimize_dfa();

    T2[0] = std::vector<int>{1, 3};
    T2[1] = std::vector<int>{2, 2};
    T2[2] = std::vector<int>{4, 4};
    T2[3] = std::vector<int>{2, 2};
    T2[4] = std::vector<int>{4, 4};
    DFA M2 = DFA(0, 2, F2, T2);
    auto min_M2 = M2.minimize_dfa();

    T3[0] = std::vector<int> {1, 2};
    T3[1] = std::vector<int> {0, 2};
    T3[2] = std::vector<int> {2, 2};
    DFA M3 = DFA(0, 2, F3, T3);
    std::cout << M3.shortest_string() << "\n";
    std::string test_M3 = "00";
    std::cout << M3.is_string_accepted(test_M3) << "\n";
    for (const auto &string: M3.strings_accepted()) {
        std::cout << string << "--";
    }

    T4[0] = std::vector<int> {1, 2};
    T4[1] = std::vector<int> {0, 3};
    T4[2] = std::vector<int> {3, 0};
    T4[3] = std::vector<int> {2, 1};
    DFA M4 = DFA(0, 2, F4, T4);
    auto min_M4 = M4.minimize_dfa();

    //phase 2
    std::map<int, std::vector<std::set<int>>> T5;
    std::set<int> empty_set {};
    T5[0] = std::vector<std::set<int>> {std::set<int> {0, 1}, std::set<int> {0}, empty_set};
    T5[1] = std::vector<std::set<int>> {empty_set, std::set<int> {2}, empty_set};
    T5[2] = std::vector<std::set<int>> {empty_set, empty_set, empty_set};
    NFA M5 = NFA(0, 2, F5, T5);
    DFA dfa_M5 = M5.convert_to_dfa();
    return 0;
}