# FiniteAutomata Class Documentation

### Overview

The `FiniteAutomata` class is a generic template class that serves as the base class for both DFAs and NFAs. It defines the fundamental properties of finite automata, such as the initial state, final states, and the transition graph. It also includes a nested `string` class to represent strings accepted by the automaton.

### Constructors

- **FiniteAutomata(int _init_state, int _alphabet_number, std::set<int> &_final_states, std::map<int, std::vector<T>> &_transition_graph)**:
  Initializes a finite automaton with the given initial state, alphabet size, final states, and transition graph.

### Member Functions

- **bool is_state_final(int _state)**:
  Checks if a state is a final state.

- **T transition_function(int _current_state, int _alphabet_letter)**:
  Returns the next state given the current state and alphabet symbol.

---

# FiniteAutomata::string Class

### Overview

The `string` class is a nested class within `FiniteAutomata` that represents a string in the automaton. It includes methods for conversion and string manipulation.

### Constructors

- **string(std::string _string)**:
  Constructs a `string` object from a `std::string`.

### Member Functions

- **std::string get_internal_string()**:
  Returns the internal `std::string` representation.

- **int length()**:
  Returns the length of the string.

- **bool operator<(string const &other_string) const**:
  Compares two strings lexicographically.

- **string operator+(char const &character) const**:
  Concatenates a character to the string.

- **static std::vector<std::string> to_string_conversion(std::vector<FiniteAutomata<T>::string> const &FA_string_vector)**:
  Converts a vector of `string` objects into a vector of `std::string` objects.

---

# DFA Class 

### Overview

The `DFA` class is derived from the `FiniteAutomata` template class and implements functionalities specific to deterministic finite automata (DFA). This class provides operations for string acceptance, string generation, and DFA minimization.

### Constructors

- **DFA(int _init_state, int _alphabet_number, std::set<int> &_final_states, std::map<int, std::vector<int>> &_transition_graph)**:
  Initializes a DFA with the given initial state, alphabet size, final states, and transition graph.

### Member Functions

- **bool is_string_accepted(std::string &_string)**:
  Determines whether the given string is accepted by the DFA based on its transition graph.

- **std::vector<std::string> specific_length_strings(int _length)**:
  Returns all strings of a specific length accepted by the DFA.

- **std::vector<std::string> strings_accepted()**:
  Returns all accepted strings by the DFA.

- **std::string longest_string()**:
  Returns the longest accepted string by the DFA.

- **std::string shortest_string()**:
  Returns the shortest accepted string by the DFA.

- **DFA minimize_dfa()**:
  Minimizes the DFA using partition refinement and produces an equivalent minimal DFA.

### Private Member Functions

- **std::vector<FiniteAutomata::string> strings_length_between(unsigned int lower_bound, unsigned int upper_bound, int max_result_num = -1)**:
  Generates strings of lengths between the specified bounds and up to a maximum number of results.

- **const std::set<std::set<int>>* procedure_mark()**:
  Marks indistinguishable state pairs in the DFA.

- **std::set<std::pair<std::set<int>, bool>> partitioning(const std::set<std::set<int>>* _unmarked_pairs)**:
  Partitions states based on indistinguishability.

- **int find_state(int state_wanted, const std::map<int, std::set<int>> &_new_old_states)**:
  Finds the new state corresponding to a given state after minimization.

- **std::map<int, std::vector<int>> creating_new_transition_graph(const std::map<int, std::set<int>> &_new_old_states)**:
  Creates a new transition graph based on the minimized states.

### Operator Overload

- **std::ostream& operator<<(std::ostream& os, const DFA& dfa)**:
  Outputs the DFA's initial state, alphabet size, final states, and transition graph.

---

# NFA Class

### Overview

The `NFA` class is derived from the `FiniteAutomata` template class and implements functionalities specific to nondeterministic finite automata (NFA). Unlike a DFA, an NFA allows multiple transitions for the same input symbol and can transition to multiple states simultaneously. This class provides operations for string acceptance, string generation, and NFA to DFA conversion.

### Constructors

- **NFA(int _init_state, int _alphabet_number, std::set<int> &_final_states, std::map<int, std::vector<int>> &_transition_graph)**:
  Initializes an NFA with the given initial state, alphabet size, final states, and transition graph.

### Member Functions

- **bool is_string_accepted(std::string &_string)**:
  Determines whether the given string is accepted by the NFA. This method considers all possible state transitions, including non-deterministic ones.

- **std::vector<std::string> specific_length_strings(int _length)**:
  Returns all strings of a specific length accepted by the NFA, considering its non-deterministic behavior.

- **std::vector<std::string> strings_accepted()**:
  Returns all accepted strings by the NFA, considering all possible state transitions.

- **std::string longest_string()**:
  Returns the longest accepted string by the NFA.

- **std::string shortest_string()**:
  Returns the shortest accepted string by the NFA.

- **DFA convert_to_dfa()**:
  Converts the NFA to an equivalent DFA using the subset construction (or powerset construction) method.

### Private Member Functions

- **std::vector<FiniteAutomata::string> strings_length_between(unsigned int lower_bound, unsigned int upper_bound, int max_result_num = -1)**:
  Generates strings of lengths between the specified bounds for the NFA.

- **std::set<int> epsilon_closure(int _state)**:
  Returns the epsilon closure of a state in the NFA, which includes all the states that can be reached via epsilon (empty) transitions.

- **std::set<int> transition_function(std::set<int> _current_states, int _alphabet_letter)**:
  Returns the set of possible next states given a set of current states and an input alphabet symbol.

- **std::set<int> get_next_states(std::set<int> _current_states, int _alphabet_letter)**:
  Returns the set of all next possible states for a given set of current states and an alphabet symbol.

### Operator Overload

- **std::ostream& operator<<(std::ostream& os, const NFA& nfa)**:
  Outputs the NFA's initial state, alphabet size, final states, and transition graph.

---

# Additional Notes

- The transition function of a DFA is assumed to operate on a binary alphabet (i.e., `0` and `1`), which is why the transition table uses indices `0` and `1` for the input symbols.
- The NFA class allows multiple transitions for the same input symbol and can reach multiple states at the same time. This is a key difference between NFAs and DFAs.
- Both `DFA` and `NFA` classes provide methods for generating strings of specific lengths or all accepted strings, based on their respective transition graphs.
- The `convert_to_dfa()` method in the NFA class uses the **subset construction** algorithm to convert an NFA to an equivalent DFA, making it possible to utilize DFA properties on NFA-based models.
