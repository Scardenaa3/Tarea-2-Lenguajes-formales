# Subset Construction Algorithm (NFA to DFA Conversion)

## Student Information
- **Full Name:** Santiago Cárdenas Angarita
- **Class Number:** SI2002 - Formal Languages

---

## Environment & Tools
- **Operating System:** Ubuntu 24.04 LTS (WSL2 / Linux)
- **Programming Language:** C++ (C++17 standard)
- **Compiler:** g++ 13.2.0 / MSVC (Microsoft Visual C++)
- **IDE / Editors:** Visual Studio Code / Visual Studio 2022

---

## Algorithm Explanation

The **Subset Construction Algorithm** (also known as Powerset Construction) converts a Non-Deterministic Finite Automaton (NFA) into an equivalent Deterministic Finite Automaton (DFA), as described by Dexter Kozen in *Automata and Computability* (Lecture 6).

### Conceptual Breakdown

1. **State Space Transformation:**
   A state in the resulting DFA represents a *subset* of states from the original NFA. If the NFA has $n$ states, the DFA can potentially have up to $2^n$ states, though only reachable states are constructed.

2. **Initial State Definition:**
   The initial state of the DFA is formed as the set of all initial states $S$ of the NFA.
   $$Q_0^{DFA} = S$$

3. **Transition Function Computation:**
   For a given subset state $R \subseteq Q$ in the DFA and an input symbol $a \in \Sigma$, the transition function $\delta_{DFA}(R, a)$ computes the set of all states reachable in the NFA from any state in $R$ via transitions labeled $a$:
   $$\delta_{DFA}(R, a) = \bigcup_{q \in R} \Delta(q, a)$$

4. **Dynamic Reachability Search (BFS):**
   - The algorithm maintains a queue of unprocessed DFA states and a hash map (`std::map<std::set<int>, int>`) to track already visited state subsets.
   - Starting with $S$, each state subset is dequeued, and its outgoing transitions for every symbol in $\Sigma$ are evaluated.
   - If a resulting set of NFA states has not been seen before, it is registered as a new DFA state and pushed to the processing queue.

5. **Accepting (Final) States:**
   A state $R$ in the DFA is designated as an accepting (final) state if it contains at least one final state from the NFA:
   $$F_{DFA} = \{ R \in Q_{DFA} \mid R \cap F_{NFA} \neq \emptyset \}$$

---

## How to Run Step-by-Step

---

### Option A: Running from Ubuntu Terminal (WSL) — Step-by-Step for Beginners

Follow these detailed steps to compile and run the project in Ubuntu, even if you have no prior experience with the command line.

#### Step 1: Open the Terminal and Navigate to Project Directory
1. Open your Ubuntu terminal application.
2. Navigate to your project folder using the `cd` command. For example:
   ```bash
   cd "/mnt/c/Users/USER/OneDrive/Desktop/Tarea 2"
