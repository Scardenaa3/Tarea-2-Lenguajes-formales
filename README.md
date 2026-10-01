# Subset Construction Algorithm (NFA to DFA Conversion)

## Student Information
- Full Name: Santiago Cárdenas Angarita
- Class Number: SI2002 - Formal Languages

---

## Environment & Tools
- Operating System: Ubuntu 24.04 LTS (WSL2 / Linux)
- Programming Language: C++ (C++17 standard)
- Compiler: g++ 13.2.0 / MSVC (Microsoft Visual C++)
- IDE / Editors: Visual Studio Code / Visual Studio 2022

---

## Algorithm Explanation

The Subset Construction Algorithm (also known as Powerset Construction) converts a Non-Deterministic Finite Automaton (NFA) into an equivalent Deterministic Finite Automaton (DFA), as described by Dexter Kozen in Automata and Computability (Lecture 6).

### Conceptual Breakdown

1. State Space Transformation:
   A state in the resulting DFA represents a subset of states from the original NFA. If the NFA has n states, the DFA can potentially have up to 2^n states, though only reachable states are constructed.

2. Initial State Definition:
   The initial state of the DFA is formed as the set of all initial states S of the NFA.
   Q0_DFA = S

3. Transition Function Computation:
   For a given subset state R in the DFA and an input symbol a in Sigma, the transition function delta_DFA(R, a) computes the set of all states reachable in the NFA from any state in R via transitions labeled a:
   delta_DFA(R, a) = Union_{q in R} Delta(q, a)

4. Dynamic Reachability Search (BFS):
   - The algorithm maintains a queue of unprocessed DFA states and a hash map (std::map<std::set<int>, int>) to track already visited state subsets.
   - Starting with S, each state subset is dequeued, and its outgoing transitions for every symbol in Sigma are evaluated.
   - If a resulting set of NFA states has not been seen before, it is registered as a new DFA state and pushed to the processing queue.

5. Accepting (Final) States:
   A state R in the DFA is designated as an accepting (final) state if it contains at least one final state from the NFA:
   F_DFA = { R in Q_DFA | R intersection F_NFA != empty_set }

---

## How to Run Step-by-Step

---

### Option A: Running from Ubuntu Terminal (WSL) — Step-by-Step for Beginners

Follow these detailed steps to compile and run the project in Ubuntu, even if you have no prior experience with the command line.

#### Step 1: Open the Terminal and Navigate to Project Directory
1. Open your Ubuntu terminal application.
2. Navigate to your project folder using the cd command:
   cd "/mnt/c/Users/USER/OneDrive/Desktop/Tarea 2"

#### Step 2: Ensure Compiler and Tools are Installed
Check if the C++ compiler is available:
   g++ --version
If not installed, run:
   sudo apt update && sudo apt install build-essential -y

#### Step 3: Compile the C++ Source Code
Compile main.cpp specifying the C++17 standard:
   g++ -std=c++17 -O2 main.cpp -o subset_const

#### Step 4: Prepare the Input File (input.txt)
Create or edit your test case file in the same directory using nano:
   nano input.txt

#### Step 5: Execute with Input Redirection
Run the compiled binary feeding input.txt directly through standard input:
   ./subset_const < input.txt

---

### Option B: Running in Visual Studio Code (WSL / Linux)

1. Open Project Folder:
   Launch VS Code and open the folder containing main.cpp (File -> Open Folder...).
2. Open Integrated Terminal:
   Press Ctrl + ~ (or go to Terminal -> New Terminal).
3. Compile:
   Execute the following command in the terminal:
   g++ -std=c++17 main.cpp -o subset_const
4. Run:
   Execute using input redirection:
   ./subset_const < input.txt

---

### Option C: Running Interactive Mode (Manual Console Entry)

If you prefer to type the input line by line directly into the console instead of reading from input.txt:

1. Launch the executable directly:
   ./subset_const
2. Paste or type the input data sequentially (Number of cases, Number of states, Initial states, Alphabet, Final states, and Transition matrix). Press Enter after each line.

---

### Option D: Running in Visual Studio 2022 (Windows / MSVC)

1. Open Visual Studio and select Create a new project -> C++ Console App.
2. Replace the generated source code in main.cpp with the project's main.cpp.
3. Set the C++ Language Standard:
   - Go to Project -> Properties -> C/C++ -> Language -> C++ Language Standard.
   - Select ISO C++17 Standard (/std:c++17) and click Apply.
4. Configure Input File Redirection:
   - Go to Project -> Properties -> Debugging -> Command Arguments.
   - Type: < input.txt
   - Copy input.txt into the project directory (where main.cpp resides).
5. Press Ctrl + F5 to compile and run without debugging.
