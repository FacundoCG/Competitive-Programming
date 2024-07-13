#include <bits/stdc++.h>
using namespace std;

void generatePermutations(string& s, vector<bool>& used, string& current, vector<string>& result) {
    if (current.size() == s.size()) {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < s.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;

        current.push_back(s[i]);
        generatePermutations(s, used, current, result);

        current.pop_back();
        used[i] = false;
    }
}

int main() {
    string s;
    cin >> s;

    sort(s.begin(), s.end());
    vector<string> result;
    vector<bool> used(s.size(), false);
    string current;
    generatePermutations(s, used, current, result);

    set<string> differentStrings;

    int m = result.size();

    for (int i = 0; i < m; i++) {
        if (differentStrings.find(result[i]) == differentStrings.end()){
            differentStrings.insert(result[i]);
        }
    }

    cout << differentStrings.size() << "\n";

    for (string s : differentStrings){
        cout << s << "\n";
    }

    return 0;
}