#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

string getNextNonEmptyLine() {
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        bool has_content = false;
        for (char c : line) {
            if (!isspace(c)) {
                has_content = true;
                break;
            }
        }
        if (has_content) return line;
    }
    return "";
}

set<int> parseSetToken(const string& str) {
    set<int> res;
    string clean = "";
    for (char c : str) {
        if (c != '{' && c != '}' && c != ',') {
            clean += c;
        } else {
            clean += ' ';
        }
    }
    stringstream ss(clean);
    int val;
    while (ss >> val) {
        if (val != 0) {
            res.insert(val);
        }
    }
    return res;
}

string formatSet(const set<int>& s) {
    if (s.empty()) return "0";
    string res = "{";
    bool first = true;
    for (int elem : s) {
        if (!first) res += " ";
        res += to_string(elem);
        first = false;
    }
    res += "}";
    return res;
}

void solveCase() {
    string line = getNextNonEmptyLine();
    if (line.empty()) return;
    int n = stoi(line);

    // 1. Estados Iniciales S
    line = getNextNonEmptyLine();
    set<int> S = parseSetToken(line);

    // 2. Alfabeto
    line = getNextNonEmptyLine();
    stringstream ss_alpha(line);
    vector<char> alphabet;
    char sym;
    while (ss_alpha >> sym) {
        alphabet.push_back(sym);
    }

    // 3. Estados Finales F
    line = getNextNonEmptyLine();
    set<int> F = parseSetToken(line);

    // 4. Transiciones NFA
    vector<vector<set<int>>> nfa_trans(n + 1, vector<set<int>>(alphabet.size()));

    for (int i = 1; i <= n; ++i) {
        line = getNextNonEmptyLine();
        stringstream ss_row(line);
        
        int state_num;
        if (ss_row >> state_num) {
            for (size_t j = 0; j < alphabet.size(); ++j) {
                string token;
                ss_row >> token;
                if (token.find('{') != string::npos && token.find('}') == string::npos) {
                    string part;
                    while (token.find('}') == string::npos && ss_row >> part) {
                        token += " " + part;
                    }
                }
                nfa_trans[state_num][j] = parseSetToken(token);
            }
        }
    }

    // --- Subset Construction ---
    map<set<int>, int> dfa_state_id;
    vector<set<int>> dfa_states;
    queue<set<int>> unprocessed;

    dfa_state_id[S] = 0;
    dfa_states.push_back(S);
    unprocessed.push(S);

    vector<vector<int>> dfa_trans;

    while (!unprocessed.empty()) {
        set<int> current = unprocessed.front();
        unprocessed.pop();

        int u_id = dfa_state_id[current];
        if (u_id >= (int)dfa_trans.size()) {
            dfa_trans.resize(u_id + 1, vector<int>(alphabet.size()));
        }

        for (size_t j = 0; j < alphabet.size(); ++j) {
            set<int> move_result;
            for (int st : current) {
                for (int nxt : nfa_trans[st][j]) {
                    move_result.insert(nxt);
                }
            }

            if (dfa_state_id.find(move_result) == dfa_state_id.end()) {
                int new_id = dfa_states.size();
                dfa_state_id[move_result] = new_id;
                dfa_states.push_back(move_result);
                unprocessed.push(move_result);
            }

            dfa_trans[u_id][j] = dfa_state_id[move_result];
        }
    }

    set<int> dfa_F;
    for (size_t i = 0; i < dfa_states.size(); ++i) {
        for (int q : dfa_states[i]) {
            if (F.count(q)) {
                dfa_F.insert(i);
                break;
            }
        }
    }

    // Imprimir encabezado de columnas
    for (char c : alphabet) {
        cout << "\t" << c;
    }
    cout << "\n";

    // Imprimir tabla de transiciones DFA
    for (size_t i = 0; i < dfa_states.size(); ++i) {
        if (i == 0 && dfa_F.count(i)) {
            cout << "<-* " << (i + 1);
        } else if (i == 0) {
            cout << "<-  " << (i + 1);
        } else if (dfa_F.count(i)) {
            cout << " *  " << (i + 1);
        } else {
            cout << "    " << (i + 1);
        }

        for (size_t j = 0; j < alphabet.size(); ++j) {
            int target_id = dfa_trans[i][j];
            cout << "\t" << formatSet(dfa_states[target_id]);
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line = getNextNonEmptyLine();
    if (!line.empty()) {
        int cases = stoi(line);
        while (cases--) {
            solveCase();
        }
    }
    return 0;
}
